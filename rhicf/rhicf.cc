#include <fstream>
#include <sstream>
#include <cstring>
#include <map>

#include <boost/filesystem.hpp>
#include <boost/format.hpp>
#include <boost/tokenizer.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/random.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/program_options.hpp>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "Randomize.hh"

#include "RHICfDetectorConstruction.hh"
#include "RHICfPhysicsList.hh"
#include "RHICfPrimaryGeneratorAction.hh"
#include "RHICfRunAction.hh"
#include "RHICfEventAction.hh"
#include "RHICfTrackingAction.hh"
#include "RHICfSteppingAction.hh"
#include "RHICfStackingAction.hh"
#include "RHICfParam.hpp"

#undef G4VIS_USE

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#define G4UI_USE_TCSH

#if defined(G4UI_USE_TCSH)
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"
#else
#include "G4UIterminal.hh"
#endif

namespace fs=boost::filesystem;
namespace pt=boost::posix_time;
namespace rn=boost::random;
namespace po=boost::program_options;
using po::options_description;
using po::value;
using po::variables_map;
using po::store;
using po::parse_config_file;
using po::notify;
using boost::lexical_cast;
typedef boost::char_separator< char > separator;
typedef boost::tokenizer< separator >::iterator iterator;


FLAGS GetFlag(G4String flagString);

int main(int argc,char** argv)
{
  if(argc==1) {
    G4cout << "No input file!" << G4endl;
    return 1;
  }

  ifstream inputs(argv[1]);
  if(inputs.fail()) assert(!"ERROR: input.dat does not exist.");

  /// Set options
  options_description opt_common("Common for all mode");
  opt_common.add_options()
    ("SIMULATION", value<std::string>(), "Simulation mode (See GeometryFiles.dat)")
    ("GEOMETRYDIR", value<fs::path>(), "Directory containing GDML files")
    ("TABLESDIR", value<fs::path>(), "Directory containing tables")
    ("OUTPUTFILE", value<fs::path>(), "Output file (ROOT file)")
    ("NEVENT", value<int>()->default_value(1000), "Number of events")
    ("RUNNUMBER", value<int>()->default_value(9999999), "Run number");
  options_description opt1("For Generate/Full/BeamTest mode");
  opt1.add_options()
    ("SEED1", value<int>()->default_value(-1), "Seed for Geant4");
  options_description opt2("For Generate/Full mode");
  opt2.add_options()
    ("CRMCDIR", value<fs::path>(), "Directory containing 'crmc'")
    ("MODEL", value<std::string>(), "Select model")
    ("SEED2", value<int>()->default_value(-1), "Seed for model");
  options_description opt3("For Transport/Full mode");
  opt3.add_options()
    ("ETACUT", value<double>()->default_value(4.8), "Rapidity cut")
    ("ECUT", value<double>()->default_value(0.5), "Energy cut in GeV")
    ("OPPOSITE", value<std::string>()->default_value("FALSE"), "If true, simulate particles in eta<0");
  options_description opt4("For Transport/Response mode");
  opt4.add_options()
    ("INPUTFILE", value<fs::path>(), "Input file");
  options_description opt5("For BeamTest mode only");
  opt5.add_options()
    ("BEAM", value<std::string>()->default_value("geantino"), "particle name (Define by Geant4)")
    ("EBEAM", value<double>()->default_value(200), "particle energy in GeV")
    ("PBEAM", value<std::string>()->default_value("UNIFORM"), "particle position");
  options_description opt("Possible options");
  opt.add(opt_common)
    .add(opt1)
    .add(opt2)
    .add(opt3)
    .add(opt4)
    .add(opt5);

  variables_map vm;
  try{
    store(parse_config_file(inputs, opt), vm);
    notify(vm);
  }catch(std::exception& ex) {
    G4cout << opt << G4endl;
    G4cout << ex.what() << G4endl;
    exit(1);
  }

  /// Check common parameters
  std::string mode;
  fs::path fgeometry;
  fs::path ftables;
  fs::path foutput;
  int nevent;
  int nrun;
  try{
    mode=vm["SIMULATION"].as<std::string>();
    fgeometry=vm["GEOMETRYDIR"].as<fs::path>();
    ftables=vm["TABLESDIR"].as<fs::path>();
    foutput=vm["OUTPUTFILE"].as<fs::path>();
    nevent=vm["NEVENT"].as<int>();
    nrun=vm["RUNNUMBER"].as<int>();
  }catch(const boost::bad_any_cast& ex) {
    G4cout << ex.what() << G4endl;
    exit(1);
  }

  /// Read geometry file
  if(!fs::exists(fgeometry)) {
    std::string mes="Directory "+ fgeometry.string() +" does not exist.";
    G4Exception("rhicf","Invalid Directory",FatalException,mes.c_str());
  }

  fs::ifstream geomfile(fgeometry/"GeometryFiles.dat");
  if(geomfile.fail()){
    std::string mes="File "+ (fgeometry.parent_path()/"GeometryFiles.dat").string() +" does not exist.";
    G4Exception("rhicf","Invalid File",FatalException,mes.c_str());
  }

  bool findmode=false;
  std::string line;
  std::string fdetector;
  Flag flag;
  G4double DetPosition;
  while(getline(geomfile, line)) {
    if(geomfile.eof()) geomfile.close();

    int i=0;
    boost::tokenizer< separator > tokenizer(line, separator(" "));
    std::string ss;
    flag.reset(bALL);
    for(iterator iter=tokenizer.begin(); iter!=tokenizer.end(); ++iter) {
      if(i==0) ss=lexical_cast<std::string>(*iter);
      if(i==1) fdetector=lexical_cast<std::string>(*iter);
      if(i==2) DetPosition=lexical_cast<double>(*iter);
      if(i==3) flag.set(GetFlag(lexical_cast<G4String>(*iter)));
      i++;
    }
    if(ss==mode) {
      findmode=true;
      break;
    }
  }
  if(!findmode)
    G4Exception("rhicf","Invalid flag",FatalException,(mode + " is not available.").c_str());

  if(0) {
    G4cout << "Input options check1" << G4endl;
    G4cout << "FULL:          " << flag.equal(bFULL)          << G4endl;
    G4cout << "GENERATE:      " << flag.check(bGENERATE)      << G4endl;
    G4cout << "TRANSPORT:     " << flag.check(bTRANSPORT)     << G4endl;
    G4cout << "RESPONSE_ARM1: " << flag.check(bRESPONSE_ARM1) << G4endl;
    G4cout << "RESPONSE_ZDC:  " << flag.check(bRESPONSE_ZDC)  << G4endl;
    G4cout << "BEAMTEST:      " << flag.check(bBEAMTEST)      << G4endl;
  }


  /// Set tables
  if(!fs::exists(ftables)) {
    std::string mes="Directory "+ ftables.string() +" does not exist.";
    G4Exception("rhicf","Invalid Directory",FatalException,mes.c_str());
  }

  /// Prepare output file
  if(foutput.branch_path()!="" && !fs::exists(foutput.branch_path())) {
    boost::system::error_code error;
    const bool result=fs::create_directories(foutput.branch_path(), error);
    if(!result || error) {
      std::string mes="Could not create directory "+foutput.branch_path().string()+".";
      G4Exception("rhicf","Invalid Directory",FatalException,mes.c_str());
    }
  }


  // Construct the default run manager
  G4RunManager* runManager=new G4RunManager;

  RHICfDetectorConstruction* detector=new RHICfDetectorConstruction();
  runManager->SetUserInitialization(detector);
  detector->SetTables(ftables.string());
  G4VUserPhysicsList* physics=new RHICfPhysicsList("QGSP_BERT");
  runManager->SetUserInitialization(physics);

  G4UserRunAction* runAction=new RHICfRunAction(detector);
  runManager->SetUserAction(runAction);
  RHICfPrimaryGeneratorAction* genAction=new RHICfPrimaryGeneratorAction();
  runManager->SetUserAction(genAction);
  G4UserEventAction* eventAction=new RHICfEventAction();
  runManager->SetUserAction(eventAction);
  G4UserTrackingAction* trackAction=new RHICfTrackingAction();
  runManager->SetUserAction(trackAction);
  G4UserSteppingAction* stepAction=new RHICfSteppingAction();
  runManager->SetUserAction(stepAction);
  G4UserStackingAction* stackAction=new RHICfStackingAction();
  runManager->SetUserAction(stackAction);

  TFile *fin;
  fs::path finput;
  int seed1;
  int seed2;
  std::string fmodel;
  Flag flag_original; flag_original.reset(bALL);
  double sigTot, sigEla, sigIne;
  if(!flag.equal(bFULL) && !flag.check(bBEAMTEST) &&
     flag.check(bTRANSPORT|bRESPONSE_ARM1|bRESPONSE_ZDC)) {
    try{
      finput=vm["INPUTFILE"].as<fs::path>();
      fin=new TFile(finput.string().c_str());
      TTree *tin=(TTree*)fin->Get("RunInfo");

      RunInfo* runInfo=new RunInfo();
      tin->SetBranchAddress("RunInfo",&runInfo);
      tin->GetEntry(0);
      /// Retrieve parameters from input file
      if(nevent>runInfo->GetNumberOfEvents())
	nevent=runInfo->GetNumberOfEvents();
      nrun=runInfo->GetRunNumber();
      fmodel=runInfo->GetModel();
      seed1=runInfo->GetSeed1();
      seed2=runInfo->GetSeed2();
      flag_original=runInfo->GetFlag();
      G4Random::setTheSeed(seed1);
      sigTot=runInfo->GetSigTot();
      sigEla=runInfo->GetSigEla();
      sigIne=runInfo->GetSigIne();
    }catch(std::exception& ex) {
      G4cerr << finput.string() << " does not exist." << G4endl;
      if(flag.check(bTRANSPORT)) {
	flag.set(bGENERATE);
	G4cerr << "If 'CRMCDIR' and 'MODEL' are defined,"  << G4endl;
	G4cerr << " the generator start..." << G4endl;
      }else if(flag.check(bRESPONSE_ARM1) ||
	       flag.check(bRESPONSE_ZDC)) {
	exit(1);
      }
    }
  }

  /// Set rapidity cut
  double etacut;
  double ecut;
  bool opposite;
  if(flag.check(bTRANSPORT)) {
    etacut=vm["ETACUT"].as<double>();
    ecut=vm["ECUT"].as<double>();
    if(vm["OPPOSITE"].as<std::string>()=="TRUE") 
      opposite=true;
    else if(vm["OPPOSITE"].as<std::string>()=="FALSE") 
      opposite=false;
    else
      G4Exception("rhicf","Invalid flag",FatalException,"OPPOSITE: TRUE/FALSE");
  }

  /// Set seed for Geant4
  if(flag.check(bGENERATE) || flag.check(bBEAMTEST)) {
    seed1=vm["SEED1"].as<int>();
    CLHEP::HepRandom::setTheEngine(new CLHEP::RanecuEngine);
    if(seed1<0) {
      /// Get time in milliseconds
      pt::ptime date_ms=pt::microsec_clock::local_time();
      long ms=date_ms.time_of_day().total_milliseconds();
      /// To generate random seed from local time
      rn::mt19937 rng( static_cast<unsigned long>(ms));
      rn::uniform_int_distribution<> seed(0, 900000000); 
      rn::variate_generator< rn::mt19937, rn::uniform_int_distribution<> > mt(rng, seed);
      seed1=mt();
    }
   /// Convert the starting seed to integer and feed it to the random engine
    G4Random::setTheSeed(seed1);
  }

  fs::path fcrmc;
  if(flag.check(bGENERATE)) {
    try{
      fcrmc=vm["CRMCDIR"].as<fs::path>();
      fmodel=vm["MODEL"].as<std::string>();
      seed2=vm["SEED2"].as<int>();

      fcrmc=fcrmc/"crmc";
      if(!fs::exists(fcrmc)) {
	std::string mes="Directory "+ fcrmc.string() +" does not exist.";
	G4Exception("rhicf","Invalid Directory",FatalException,mes.c_str());
      }
    }catch(const boost::bad_any_cast& ex) {
      G4cout << ex.what() << G4endl;
      exit(1);
    }
  }

  std::string bParticle;
  double bEnergy;
  std::string bPosition;
  if(flag.check(bBEAMTEST)) {
    bParticle=vm["BEAM"].as<std::string>();
    bEnergy=vm["EBEAM"].as<double>();
    bPosition=vm["PBEAM"].as<std::string>();
    seed2=0;
  }

  detector->SetGeometry(fgeometry.string(),fdetector,flag);
  dynamic_cast<RHICfRunAction*>(runAction)->SetFlag_Detector(flag);
  dynamic_cast<RHICfRunAction*>(runAction)->SetFlag_Original(flag_original);
  dynamic_cast<RHICfRunAction*>(runAction)->SetSeed1(seed1);
  dynamic_cast<RHICfRunAction*>(runAction)->SetSeed2(seed2);
  dynamic_cast<RHICfRunAction*>(runAction)->SetNevent(nevent);
  dynamic_cast<RHICfRunAction*>(runAction)->SetRunNumber(nrun);
  dynamic_cast<RHICfRunAction*>(runAction)->SetModel(fmodel);
  dynamic_cast<RHICfRunAction*>(runAction)->SetOutput(foutput.string());
 if(flag.check(bBEAMTEST)) {
    dynamic_cast<RHICfPrimaryGeneratorAction*>(genAction)->SetGenerator("BeamTest");
    dynamic_cast<RHICfPrimaryGeneratorAction*>(genAction)->SetBeam(bParticle,bEnergy*CLHEP::GeV,bPosition,DetPosition);
  }else if(flag.equal(bFULL)) {
    dynamic_cast<RHICfPrimaryGeneratorAction*>(genAction)->SetGenerator("Generate");
    dynamic_cast<RHICfRunAction*>(runAction)->SetCRMCpath(fcrmc.string());
  }else if(flag.check(bGENERATE)) {
    dynamic_cast<RHICfRunAction*>(runAction)->SetCRMCpath(fcrmc.string());
  }else if(flag.check(bTRANSPORT)) {
    dynamic_cast<RHICfPrimaryGeneratorAction*>(genAction)->SetGenerator("Transport");
    dynamic_cast<RHICfPrimaryGeneratorAction*>(genAction)->SetInput(fin);
    if(flag.check(bGENERATE)) detector->SetCuts(etacut, ecut, opposite);
    else dynamic_cast<RHICfPrimaryGeneratorAction*>(genAction)->SetCuts(etacut, ecut, opposite);
  }else if(flag.check(bRESPONSE_ARM1) || flag.check(bRESPONSE_ZDC)) {
    dynamic_cast<RHICfPrimaryGeneratorAction*>(genAction)->SetGenerator("Response");
    dynamic_cast<RHICfPrimaryGeneratorAction*>(genAction)->SetInput(fin);
  }else{
    G4Exception("rhicf","Invalid flag",FatalException,"Not available.");
  }

  // Initialize G4 kernel
  runManager->Initialize();

#ifdef G4VIS_USE
  // Initialize visualization
  G4VisManager* visManager=new G4VisExecutive;
  visManager->Initialize();
#endif

  // Get the pointer to the User Interface manager
  G4UImanager* UI=G4UImanager::GetUIpointer();

  if(0) {
    // interactive mode : define visualization UI terminal
    G4UIsession* session = 0;
#if defined(G4UI_USE_TCSH)
    session = new G4UIterminal(new G4UItcsh);
#else
    session = new G4UIterminal();
#endif
    session->SessionStart();
    delete session;
  }else{
    std::stringstream sevent;
    sevent<<nevent;
    UI->ApplyCommand("/run/beamOn "+sevent.str());
    return 0;
  }

  return 0;
}


FLAGS GetFlag(G4String flagString)
{
  if(flagString=="bGENERATE")           return bGENERATE;
  else if(flagString=="bTRANSPORT")     return bTRANSPORT;
  else if(flagString=="bRESPONSE_ARM1") return bRESPONSE_ARM1;
  else if(flagString=="bRESPONSE_ZDC")  return bRESPONSE_ZDC;
  else if(flagString=="bRESPONSE")      return bRESPONSE;
  else if(flagString=="bBEAMTEST")      return bBEAMTEST;
  else if(flagString=="bBEAMTEST_ARM1") return bBEAMTEST_ARM1;
  else if(flagString=="bBEAMTEST_ZDC")  return bBEAMTEST_ZDC;
  else if(flagString=="bBEAMTEST_ALL")  return bBEAMTEST_ALL;
  else if(flagString=="bFULL")          return bFULL;
  else if(flagString=="bALL")           return bALL;
  else                                  return bNONE;
}
