#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <cstring>
#include <fstream>
#include <iostream>
#include <iomanip>

#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/program_options.hpp>

#include "TFile.h"
#include "TChain.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TGraph.h"
#include "TCanvas.h"
#include "TSpectrum.h"
#include "TVectorD.h"
#include "TMatrixD.h"
#include "TRandom3.h"
#include "TMath.h"

#include "RHICfSimEvent.hpp"

namespace fs=boost::filesystem;

using boost::program_options::options_description;
using boost::program_options::value;
using boost::program_options::variables_map;
using boost::program_options::store;
using boost::program_options::parse_command_line;
using boost::program_options::notify;
using boost::lexical_cast;

typedef boost::char_separator< char > separator;
typedef boost::tokenizer< separator >::iterator iterator;

using namespace std;

int main(int argc, char **argv)
{
  cout << getenv("RHICF_LIB") << endl;

  options_description opt("For Help");
  opt.add_options()
    ("help,h", "Display help")
    ("output,o", value<string>(), "Output file")
    ("indir,i",  value<fs::path>(), "Input directory")
    ("first,f",  value<int>(),      "First file number")
    ("last,l",    value<int>(),     "Last file number")
    ;

  variables_map vm;
  store(parse_command_line(argc, argv, opt), vm);
  notify(vm);

  if(vm.count("help")   ||
     !vm.count("first") || !vm.count("last") ||
     !vm.count("indir") || !vm.count("indir")) {
    cerr << opt << endl;
    exit(1);
  }
  
  string outname = vm["output"].as<string>();
  fs::path indir = vm["indir"].as<fs::path>();
  int first      = vm["first"].as<int>();
  int last       = vm["last"].as<int>();

  TFile* fout=new TFile(outname.c_str(), "recreate");

  char hname[256];

  TH1D *h_trigger[ntower];
  for(int itower=0; itower<ntower; itower++) {
    sprintf(hname, "trigger_tow%d",itower);
    h_trigger[itower]=new TH1D(hname,hname,255,0,255);
  }

  TChain* tevent=new TChain("EventInfo","");
  for(int ifile=first; ifile<=last; ifile++) {
    fs::path afile("run"+boost::lexical_cast<string>(ifile)+".root");
    string fname=(fs::absolute(indir) / afile).string();
    if(0) cout << "Add " << fname << endl;
    tevent->Add(fname.c_str());
  }
  tevent->SetMakeClass(1);

  ForwardContainer* forwardCont=new ForwardContainer();
  MCDataContainer* mcCont=new MCDataContainer();
  ZDCContainer* zdcCont=new ZDCContainer();

  tevent->SetBranchAddress("forward", &forwardCont);
  tevent->SetBranchAddress("mc", &mcCont);
  tevent->SetBranchAddress("zdc", &zdcCont);

  vector<Forward*> forward;
  vector<vector<double> > plate;
  vector<vector<vector<vector<double> > > > bar;
  vector<double> zdc;
  vector<vector<double> > smd;
  vector<int> nphoton;

  double weight[nplate]={1,1,1,1,1,1,1,1,
			 1,1,1,2,2,2,2,2};

  int nevent;
  nevent=tevent->GetEntries();
  for(int ievent=0; ievent<nevent; ievent++) {
    tevent->GetEntry(ievent);

    forward=forwardCont->GetContainer();
    plate=mcCont->GetPlate();
    bar=mcCont->GetBarTruth();
    zdc=zdcCont->GetZDC();
    smd=zdcCont->GetSMD();
    nphoton=zdcCont->GetNphoton();

    double posx=forward[0]->GetPosition().X();
    double posy=forward[0]->GetPosition().Y();

    double edge=2.;
    int flag=2;
    if(posy < +posx+(10.-edge)*sqrt(2.) &&
       posy < -posx+(10.-edge)*sqrt(2.) &&
       posy > +posx-(10.-edge)*sqrt(2.) &&
       posy > -posx-(10.-edge)*sqrt(2.)) {
      flag=0;
    }else if(posy < +posx+(50.-edge)*sqrt(2.)+5. &&
	     posy < -posx+(50.-edge)*sqrt(2.)+5. &&
	     posy > +posx+(10.+edge)*sqrt(2.)+5. &&
	     posy > -posx+(10.+edge)*sqrt(2.)+5.) {
      flag=1;
    }
    if(flag==2) continue;

    bool btrg[ntower]={};
    double thr=25;
    for(int itower=0; itower<ntower; itower++) {
      for(int iplate=0; iplate<nplate-2; iplate++) {
	if(plate[itower][iplate+0]>thr &&
	   plate[itower][iplate+1]>thr &&
	   plate[itower][iplate+2]>thr) {
	  btrg[itower]=true;
	}
      }
    }

    if(btrg[flag])
      h_trigger[flag]->Fill(forward[0]->GetMomentum().Pz());

  }

  fout->Write();
  fout->Close();

  return 0;
}

