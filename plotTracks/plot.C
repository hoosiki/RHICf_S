{
  gROOT->Reset();

  gSystem->Load("libGeom");
  gSystem->Load("libGdml");

  TGeoManager::Import("rhicf.gdml");

  TList* mat = gGeoManager->GetListOfMaterials();
  TIter next(mat);
  TObject *obj;
  while(obj = next()) obj->Print();

  gGeoManager->CheckOverlaps(0.01);
  gGeoManager->PrintOverlaps();

  TIter next(gGeoManager->GetListOfOverlaps());
  int count = 0;
  TGeoOverlap* overlap;
  while ((overlap=(TGeoOverlap*)next())) {
    gGeoManager->GetListOfOverlaps()->At(count)->Draw();
    ++count;
  }

  TObjArray *va = gGeoManager->GetListOfVolumes();
  int nv = va->GetEntries();
  for(int i = 0; i < nv; i++) {
    TGeoVolume *v = (TGeoVolume*)va->At(i);
    cout << "Volume" << i
	 << " Name: " << v->GetName()
	 << " Mat: " << v->GetMaterial()->GetName()
	 << endl;
    string m = v->GetMaterial()->GetName();

    v->SetTransparency(90);

    if(m=="Galactic") v->SetInvisible();
    else if(m=="Air") v->SetInvisible();
    else if(m=="Beryllium") v->SetLineColor(kGray);
    else if(m=="Iron") v->SetLineColor(kGray);
    else if(m=="Duralumin") v->SetInvisible();//v->SetLineColor(kCyan-10);
    else if(m=="Aluminium") v->SetInvisible();// v->SetLineColor(kGray);
    else if(m=="G10") v->SetLineColor(kGreen-10);
    else if(m=="Acrylic") v->SetLineColor(kWhite);
    else if(m=="Tungsten") v->SetLineColor(kGray+2);
    else if(m=="GSO") v->SetLineColor(kCyan);
    else if(m=="GSObar") v->SetLineColor(kRed);
    else if(m=="Quartz") v->SetLineColor(kYellow);
    else if(m=="FPMMA") v->SetLineColor(kGreen);
    else if(m=="PMMA") v->SetLineColor(kCyan);
    else if(m=="Aluminium") v->SetLineColor(kGray-1);
    else if(m=="Lead") v->SetLineColor(kGray);
    else if(m=="Scintillator") v->SetLineColor(kCyan-1);
  }

  gGeoManager->GetTopVolume()->Draw("ogl");


  ifstream indata("steps.log");

  int id,parentid,pdg;
  double mom[3];;
  double pos1[3];
  string vol1;
  double pos2[3];
  string vol2;

  TDatabasePDG* p=TDatabasePDG::Instance();
  TPolyLine3D* track[99999999];
  double momz[99999999]={};
  int pdgcode[99999999]={};
  int old_id=0;
  int ntrack=0;
  int ip=0;
  iline=1;
  while(indata>>id>>parentid>>pdg
	>>mom[0]>>mom[1]>>mom[2]
	>>pos1[0]>>pos1[1]>>pos1[2]>>vol1
	>>pos2[0]>>pos2[1]>>pos2[2]>>vol2) {
    if(old_id!=id) {
      ip=0;
      track[id-1]=new TPolyLine3D();
      track[id-1]->SetPoint(ip,pos1[0]/10,pos1[1]/10,pos2[2]/10);
      momz[id-1]=mom[2];
      pdgcode[id-1]=pdg;
      old_id=id;
      ip++;
      ntrack++;
    }
    track[id-1]->SetPoint(ip,pos2[0]/10,pos2[1]/10,pos2[2]/10);

    ip++;
  }

  cout << ntrack << endl;

  for(int i=0; i<ntrack; i++) {
    TParticlePDG* a=p->GetParticle(pdgcode[i]);
    if(pdgcode[i]>1000000000) continue;
    if(momz[i]<300) continue;
    //    if(a->Charge()==0) track[i]->SetLineColor(3);
    if(i==0) track[i]->SetLineColor(3);
    if(a->Charge()==0 && i!=0) continue;
    else if(a->Charge()>0) track[i]->SetLineColor(2);
    else if(a->Charge()<0) track[i]->SetLineColor(4);
    track[i]->SetLineWidth(2);

    track[i]->Draw("same");
  }
  indata.close();
}
