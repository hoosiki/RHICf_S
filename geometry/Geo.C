///
{
  gSystem->Load("libGeom");
  gSystem->Load("libGdml");

  //Junsang****TGeoManager::Import("zdc_star.gdml");
  //Junsang****TGeoManager::Import("response_pos1.gdml");
  //Junsang****TGeoManager::Import("response_pos2.gdml");
  //Junsang****TGeoManager::Import("response_pos3.gdml");
  //Junsang****TGeoManager::Import("response_pos4.gdml");
  //Junsang****TGeoManager::Import("pipe_star.gdml");
  //Junsang****TGeoManager::Import("pipe_phenix.gdml");
  //Junsang****TGeoManager::Import("pipe_nostructure.gdml");
  //Junsang****TGeoManager::Import("full_pos1.gdml");
  //Junsang****TGeoManager::Import("full_pos2.gdml");
  //Junsang****TGeoManager::Import("full_pos3.gdml");
  //Junsang****TGeoManager::Import("full_pos4.gdml");
  //Junsang****TGeoManager::Import("full_nopipe_pos1.gdml");
  //Junsang****TGeoManager::Import("full_nopipe_pos2.gdml");
  //Junsang****TGeoManager::Import("full_nopipe_pos3.gdml");
  //Junsang****TGeoManager::Import("full_nopipe_pos4.gdml");
  //Junsang****TGeoManager::Import("beamtest_pos1.gdml");
  //Junsang****TGeoManager::Import("beamtest_pos2.gdml");
  //Junsang****TGeoManager::Import("beamtest_pos3.gdml");
  //Junsang****TGeoManager::Import("beamtest_pos4.gdml");
  TGeoManager::Import("beamtest_zdc.gdml");
  //Junsang****TGeoManager::Import("central.gdml");
  //Junsang****TGeoManager::Import("bbc.gdml");
  //Junsang****TGeoManager::Import("arm1.gdml");
  //Junsang****TGeoManager::Import("beamtest_pos1.gdml");



  TList* mat = gGeoManager->GetListOfMaterials();
  TIter next(mat);
  TObject *obj;
  while(obj = next()) obj->Print();

  gGeoManager->CheckOverlaps(0.01);
  gGeoManager->PrintOverlaps();

  TObjArray *va = gGeoManager->GetListOfVolumes();
  int nv = va->GetEntries();
  for(int i = 0; i < nv; i++) {
    TGeoVolume *v = (TGeoVolume*)va->At(i);
    cout << "Volume" << i
	 << " Name: " << v->GetName()
	 << " Mat: " << v->GetMaterial()->GetName()
	 << endl;
    string m = v->GetMaterial()->GetName();


    if(m=="Duralumin") v->SetInvisible();//v->SetLineColor(kCyan-10);
    else if(m=="Aluminium") {
      v->SetLineColor(kGray);
      v->SetTransparency(70);
    }
    else if(m=="G10") {
      v->SetLineColor(kGreen-10);
      v->SetTransparency(80);
    }
    else if(m=="Acrylic")  {
      v->SetLineColor(kWhite);
      v->SetTransparency(80);
    }
    else if(m=="Tungsten") v->SetLineColor(kGray+2);
    else if(m=="GSO") v->SetLineColor(kCyan);
    else if(m=="GSObar") v->SetLineColor(kRed);
    else if(m=="Quartz") {
      v->SetLineColor(kYellow);
      v->SetTransparency(50);
    }
    else if(m=="BeamGas") v->SetLineColor(kYellow);

    /*
    else if(m=="Scintillator") v->SetLineColor(kCyan);
      v->SetFillColor(kOrange);
    }
      cout << v->GetFillColor() << endl;
    */
  }

  gGeoManager->GetTopVolume()->Draw("ogl");
}
