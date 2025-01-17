#include "HCALLMapProducer.h"
#include "HCALTPProducer.h"
#include "HCALLMapLoader.h"
#include "HCALLMapDumper.h"
#include "HCALLMapChecker.h"

int main(int argc, char* argv[])
{
  std::string RunMode, PrdMode;
  if(argc <= 1){
    std::cerr <<"#Please give at least 2 argument " << "RunMode ProduceMode" << std::endl;
    std::cerr <<"# Valid configurations are " << std::endl;
    std::cerr <<"# ./HCALLMapAnalyzer RunMode PrdMode" << std::endl;
    return -1;
  }else if (argc == 2){
    RunMode = argv[1];
    if(RunMode.find("HBHEUMap")!=std::string::npos || RunMode.find("HBHEUMapCalib")!=std::string::npos || RunMode.find("HBHEPedLMap")!=std::string::npos || RunMode.find("HBHELMapCalib")!=std::string::npos)
      PrdMode = RunMode;
    else{
      std::cerr << "The input RunMode is invalid!";
      return -1;
    }
  }else if(argc >= 3){
    RunMode = argv[1];
    PrdMode = argv[2];
  }

  std::cout << "#The valid run modes are: HB, HE, HF, HO, HBHEUMap, HBHEUMapCalib, HBHEPedLMap, HBHELMapCalib" << std::endl;
  std::cout << "#The run mode we have right now is: " << RunMode << std::endl;
  std::cout << "#The valid run modes are: LMap, EMap, FMap, HT, LMapCalib, EMapCalib" << std::endl;
  std::cout << "#The produce mode we have right now is: " << PrdMode << std::endl;

  HCALTPProducer myHCALTPProducer;
  HCALLMapLoader myHCALLMapLoader;
  HCALLMapDumper myHCALLMapDumper;
  HCALLMapChecker myHCALLMapChecker;

  if( RunMode == "HB" )
  {/*
    HBMappingAlgorithm myHBMappingAlgorithm;
    myHBMappingAlgorithm.ConstructHBLMapObject("Normal");
    myHBMappingAlgorithm.ConstructHBLMapObject("Calib");
    bool passCollisionCheck = myHCALLMapChecker.checkHBLMapObject(myHBMappingAlgorithm.myHBFrontEnd, myHBMappingAlgorithm.myHBBackEnd, myHBMappingAlgorithm.myHBHPD, myHBMappingAlgorithm.myHBGeometry, myHBMappingAlgorithm.myHBTriggerTower);
    if( passCollisionCheck ){ std::cout << "#Map pass collision check, Good!" << std::endl; }
    else{ std::cout << "#Did not pass collision check! Please check!" << std::endl; return -1;}
*/
    
    ngHBMappingAlgorithm myngHBMappingAlgorithm;
    myngHBMappingAlgorithm.ConstructngHBLMapObject("Normal");
    myngHBMappingAlgorithm.ConstructngHBLMapObject("Calib");
    bool passCollisionCheck = myHCALLMapChecker.checkngHBLMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);
    if( passCollisionCheck ){ std::cout << "#Map pass collision check, Good!" << std::endl; }
    else{ std::cout << "#Did not pass collision check! Please check!" << std::endl; return -1;}
    

    if( PrdMode == "LMap" )
    {
     // myHCALLMapDumper.printHBLMapObject(myHBMappingAlgorithm.myHBFrontEnd, myHBMappingAlgorithm.myHBBackEnd, myHBMappingAlgorithm.myHBHPD, myHBMappingAlgorithm.myHBGeometry, myHBMappingAlgorithm.myHBTriggerTower);
     // myHCALLMapDumper.makedbHBLMapObject("officialMap/HCALLogicalMap.db", "HBLogicalMap",
     //                                     myHBMappingAlgorithm.myHBFrontEnd, myHBMappingAlgorithm.myHBBackEnd, myHBMappingAlgorithm.myHBHPD, myHBMappingAlgorithm.myHBGeometry, myHBMappingAlgorithm.myHBTriggerTower);
      myHCALLMapDumper.printngHBLMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower, myngHBMappingAlgorithm.myngHBTriggerTowerFiber);
      myHCALLMapDumper.makedbngHBLMapObject("officialMap/HCALLogicalMap.db", "ngHBLogicalMap",
                                            myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);
    }
    if( PrdMode == "EMap" )
    {
      //myHCALLMapDumper.printHBEMapObject(myHBMappingAlgorithm.myHBFrontEnd, myHBMappingAlgorithm.myHBBackEnd, myHBMappingAlgorithm.myHBHPD, myHBMappingAlgorithm.myHBGeometry, myHBMappingAlgorithm.myHBTriggerTower);
      myHCALLMapDumper.printngHBEMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);
    }
    if( PrdMode == "FMap" )
    {
      //myHCALLMapDumper.printHBFrontEndMapObject(myHBMappingAlgorithm.myHBFrontEnd, myHBMappingAlgorithm.myHBBackEnd, myHBMappingAlgorithm.myHBHPD, myHBMappingAlgorithm.myHBGeometry, myHBMappingAlgorithm.myHBTriggerTower);
      myHCALLMapDumper.printngHBFrontEndMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);
    }
    if( PrdMode == "EMapHT" )
    {
      //myHCALTPProducer.printHBHTEMapObject(myHBMappingAlgorithm.myHBFrontEnd, myHBMappingAlgorithm.myHBBackEnd, myHBMappingAlgorithm.myHBHPD, myHBMappingAlgorithm.myHBGeometry, myHBMappingAlgorithm.myHBTriggerTower);
      myHCALTPProducer.printngHBHTEMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower, myngHBMappingAlgorithm.myngHBTriggerTowerFiber);
    }
    if( PrdMode == "LMapCalib")
    {
      myHCALLMapDumper.printngHBCalibLMapObject(myngHBMappingAlgorithm.myngHBCalib);
      myHCALLMapDumper.makedbngHBCalibLMapObject("officialMap/HCALLogicalMap.db", "ngHBCalibLogicalMap", myngHBMappingAlgorithm.myngHBCalib);
    }
    if( PrdMode == "EMapCalib" )
    {
      myHCALLMapDumper.printngHBCalibEMapObject(myngHBMappingAlgorithm.myngHBCalib);
    }
    return 1;
  }
  else if( RunMode == "HE" )
  {
    ngHEMappingAlgorithm myngHEMappingAlgorithm;
    myngHEMappingAlgorithm.ConstructngHELMapObject("Normal");
    //myngHEMappingAlgorithm.ConstructngHELMapObject("2017HEP17");
    myngHEMappingAlgorithm.ConstructngHELMapObject("Calib");
    bool passCollisionCheck = myHCALLMapChecker.checkngHELMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
    if( passCollisionCheck ){ std::cout << "#Map pass collision check, Good!" << std::endl; }
    else{ std::cout << "#Did not pass collision check! Please check!" << std::endl; return -1;}
    if( PrdMode == "LMap" )
    {
      myHCALLMapDumper.printngHELMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
      myHCALLMapDumper.makedbngHELMapObject("officialMap/HCALLogicalMap.db", "ngHELogicalMap",
                                            myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
      //myHCALLMapDumper.makedbngHELMapObject("officialMap/HCALLogicalMap.db", "ngHEP172017LogicalMap",
      //                                      myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
    }
    if( PrdMode == "EMap" )
    {
      myHCALLMapDumper.printngHEEMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
    }
    if( PrdMode == "FMap" )
    {
      myHCALLMapDumper.printngHEFrontEndMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
    }
    if( PrdMode == "EMapHT" )
    {
      myHCALTPProducer.printngHEHTEMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
    }
    if( PrdMode == "LMapCalib" )
    {
      myHCALLMapDumper.printngHECalibLMapObject(myngHEMappingAlgorithm.myngHECalib);
      myHCALLMapDumper.makedbngHECalibLMapObject("officialMap/HCALLogicalMap.db", "ngHECalibLogicalMap", myngHEMappingAlgorithm.myngHECalib);
    }
    if( PrdMode == "EMapCalib" )
    {
      myHCALLMapDumper.printngHECalibEMapObject(myngHEMappingAlgorithm.myngHECalib);
    }
    return 1;
  }
  else if( RunMode == "HF" )
  {
    //HFMappingAlgorithm myHFMappingAlgorithm;
    //myHFMappingAlgorithm.ConstructHFLMapObject();
    
    ngHFMappingAlgorithm myngHFMappingAlgorithm;
    myngHFMappingAlgorithm.ConstructngHFLMapObject("Normal");
    myngHFMappingAlgorithm.ConstructngHFLMapObject("Calib");
    //myngHFMappingAlgorithm.SplitngHFfromOldHF(myHFMappingAlgorithm.myHFFrontEnd, myHFMappingAlgorithm.myHFBackEnd, myHFMappingAlgorithm.myHFPMTBox, myHFMappingAlgorithm.myHFGeometry, myHFMappingAlgorithm.myHFTriggerTower);
    bool passCollisionCheck = myHCALLMapChecker.checkngHFLMapObject(myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower);
    if( passCollisionCheck ){ std::cout << "#Map pass collision check, Good!" << std::endl; }
    else{ std::cout << "#Did not pass collision check! Please check!" << std::endl; return -1;}
    if( PrdMode == "LMap" )
    {
      //myHCALLMapDumper.printHFLMapObject(myHFMappingAlgorithm.myHFFrontEnd, myHFMappingAlgorithm.myHFBackEnd, myHFMappingAlgorithm.myHFPMTBox, myHFMappingAlgorithm.myHFGeometry, myHFMappingAlgorithm.myHFTriggerTower);
      myHCALLMapDumper.printngHFLMapObject(myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower);
      myHCALLMapDumper.makedbngHFLMapObject("officialMap/HCALLogicalMap.db", "ngHFLogicalMap",
                                            myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower);
    }
    if( PrdMode == "EMap" )
    {
      myHCALLMapDumper.printngHFEMapObject(myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower);
    }
    if( PrdMode == "FMap" )
    {
      myHCALLMapDumper.printngHFFrontEndMapObject(myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower);
    }
    if( PrdMode == "EMapHT" )
    {
      myHCALTPProducer.printngHFHTEMapObject(myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower);
    }
    if( PrdMode == "LMapCalib" )                                                                                                                                                                            
    {
      myHCALLMapDumper.printngHFCalibLMapObject(myngHFMappingAlgorithm.myngHFCalib);
      myHCALLMapDumper.makedbngHFCalibLMapObject("officialMap/HCALLogicalMap.db", "ngHFCalibLogicalMap", myngHFMappingAlgorithm.myngHFCalib);
    }
    if( PrdMode == "EMapCalib" )
    {
      myHCALLMapDumper.printngHFCalibEMapObject(myngHFMappingAlgorithm.myngHFCalib);
    }
    if( PrdMode == "UMap" )
    {
      myHCALLMapDumper.printngHFUMapObject(myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower, myngHFMappingAlgorithm.myngHFCalib);
      myHCALLMapDumper.makedbngHFUMapObject("officialMap/HCALLogicalMap.db", "ngHFUniversalMap",
                                          myngHFMappingAlgorithm.myngHFFrontEnd, myngHFMappingAlgorithm.myngHFBackEnd, myngHFMappingAlgorithm.myngHFPMTBox, myngHFMappingAlgorithm.myngHFGeometry, myngHFMappingAlgorithm.myngHFTriggerTower, myngHFMappingAlgorithm.myngHFCalib);
    }
    return 1;
  }
  else if( RunMode == "HO" )
  {
    //HOMappingAlgorithm myHOMappingAlgorithm;
    //so sorry no HO mapping algorithm for now... in a mess... directly load from generation G mapping algotrithm
    //int NChannel = myHCALLMapLoader.GetHOFromLMap("officialMap/eraG/HCALmapHO_G.txt", myHOMappingAlgorithm.myHOFrontEnd, myHOMappingAlgorithm.myHOBackEnd, myHOMappingAlgorithm.myHOSiPM, myHOMappingAlgorithm.myHOGeometry, myHOMappingAlgorithm.myHOTriggerTower);
    //myHOMappingAlgorithm.ConstructHOLMapObject("Calib");

    ngHOMappingAlgorithm myngHOMappingAlgorithm;
    // ngHO mapping algorithm is currently implemented by Ashraf, which can be found under the folder: CMSngHOMAP
    // Here will load ngHO LMap file and dump
    int Nchannel = myHCALLMapLoader.GetngHOFromLMap("officialMap/eraN/HCALmapngHO_N.txt",
							myngHOMappingAlgorithm.myngHOFrontEnd, myngHOMappingAlgorithm.myngHOBackEnd, myngHOMappingAlgorithm.myngHOSiPM, myngHOMappingAlgorithm.myngHOGeometry, myngHOMappingAlgorithm.myngHOTriggerTower,
							myngHOMappingAlgorithm.myngHOCalib);
    if( PrdMode == "LMap" )
    {
      //myHCALLMapDumper.printHOLMapObject(myHOMappingAlgorithm.myHOFrontEnd, myHOMappingAlgorithm.myHOBackEnd, myHOMappingAlgorithm.myHOSiPM, myHOMappingAlgorithm.myHOGeometry, myHOMappingAlgorithm.myHOTriggerTower);
      //myHCALLMapDumper.makedbHOLMapObject("officialMap/HCALLogicalMap.db", "HOLogicalMap",
      //                                    myHOMappingAlgorithm.myHOFrontEnd, myHOMappingAlgorithm.myHOBackEnd, myHOMappingAlgorithm.myHOSiPM, myHOMappingAlgorithm.myHOGeometry, myHOMappingAlgorithm.myHOTriggerTower);
      
      myHCALLMapDumper.printngHOLMapObject(myngHOMappingAlgorithm.myngHOFrontEnd, myngHOMappingAlgorithm.myngHOBackEnd, myngHOMappingAlgorithm.myngHOSiPM, myngHOMappingAlgorithm.myngHOGeometry, myngHOMappingAlgorithm.myngHOTriggerTower);
      myHCALLMapDumper.makedbngHOLMapObject("officialMap/HCALLogicalMap.db", "ngHOLogicalMap",
                                          myngHOMappingAlgorithm.myngHOFrontEnd, myngHOMappingAlgorithm.myngHOBackEnd, myngHOMappingAlgorithm.myngHOSiPM, myngHOMappingAlgorithm.myngHOGeometry, myngHOMappingAlgorithm.myngHOTriggerTower);
    }
    if( PrdMode == "EMap" )
    {
      //myHCALLMapDumper.printHOEMapObject(myHOMappingAlgorithm.myHOFrontEnd, myHOMappingAlgorithm.myHOBackEnd, myHOMappingAlgorithm.myHOSiPM, myHOMappingAlgorithm.myHOGeometry, myHOMappingAlgorithm.myHOTriggerTower);
      myHCALLMapDumper.printngHOEMapObject(myngHOMappingAlgorithm.myngHOFrontEnd, myngHOMappingAlgorithm.myngHOBackEnd, myngHOMappingAlgorithm.myngHOSiPM, myngHOMappingAlgorithm.myngHOGeometry, myngHOMappingAlgorithm.myngHOTriggerTower);
    }
    if( PrdMode == "FMap" )
    {
      //myHCALLMapDumper.printHOFrontEndMapObject(myHOMappingAlgorithm.myHOFrontEnd, myHOMappingAlgorithm.myHOBackEnd, myHOMappingAlgorithm.myHOSiPM, myHOMappingAlgorithm.myHOGeometry, myHOMappingAlgorithm.myHOTriggerTower);
    }
    
    //Added by Yuan
    if( PrdMode == "LMapCalib" )
    {
      //myHCALLMapDumper.printHOCalibLMapObject(myHOMappingAlgorithm.myHOCalib);
      //myHCALLMapDumper.makedbHOCalibLMapObject("officialMap/HCALLogicalMap.db", "HOCalibLogicalMap" , myHOMappingAlgorithm.myHOCalib );
      
      myHCALLMapDumper.printngHOCalibLMapObject(myngHOMappingAlgorithm.myngHOCalib);
      myHCALLMapDumper.makedbngHOCalibLMapObject("officialMap/HCALLogicalMap.db", "ngHOCalibLogicalMap" , myngHOMappingAlgorithm.myngHOCalib );
    }
    if( PrdMode == "EMapCalib" )
    {
      myHCALLMapDumper.printngHOCalibEMapObject(myngHOMappingAlgorithm.myngHOCalib);
    }
    if( PrdMode == "UMap" )
    {
      //myHCALLMapDumper.printHOUMapObject(myHOMappingAlgorithm.myHOFrontEnd, myHOMappingAlgorithm.myHOBackEnd, myHOMappingAlgorithm.myHOSiPM, myHOMappingAlgorithm.myHOGeometry, myHOMappingAlgorithm.myHOTriggerTower, myHOMappingAlgorithm.myHOCalib);
      //myHCALLMapDumper.makedbHOUMapObject("officialMap/HCALLogicalMap.db", "HOUniversalMap",
      //                                    myHOMappingAlgorithm.myHOFrontEnd, myHOMappingAlgorithm.myHOBackEnd, myHOMappingAlgorithm.myHOSiPM, myHOMappingAlgorithm.myHOGeometry, myHOMappingAlgorithm.myHOTriggerTower, myHOMappingAlgorithm.myHOCalib);
      
      myHCALLMapDumper.printngHOUMapObject(myngHOMappingAlgorithm.myngHOFrontEnd, myngHOMappingAlgorithm.myngHOBackEnd, myngHOMappingAlgorithm.myngHOSiPM, myngHOMappingAlgorithm.myngHOGeometry, myngHOMappingAlgorithm.myngHOTriggerTower, myngHOMappingAlgorithm.myngHOCalib);
      myHCALLMapDumper.makedbngHOUMapObject("officialMap/HCALLogicalMap.db", "ngHOUniversalMap",
                                          myngHOMappingAlgorithm.myngHOFrontEnd, myngHOMappingAlgorithm.myngHOBackEnd, myngHOMappingAlgorithm.myngHOSiPM, myngHOMappingAlgorithm.myngHOGeometry, myngHOMappingAlgorithm.myngHOTriggerTower, myngHOMappingAlgorithm.myngHOCalib);
    }
    return 1;

  }
  else if( RunMode == "HBHEUMap" )
  {
    ngHBMappingAlgorithm myngHBMappingAlgorithm;
    myngHBMappingAlgorithm.ConstructngHBLMapObject("Normal");
    myngHBMappingAlgorithm.ConstructngHBLMapObject("Calib");
    bool passCollisionCheck = myHCALLMapChecker.checkngHBLMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);
    if( passCollisionCheck ){ std::cout << "#HB Map pass collision check, Good!" << std::endl; }
    else{ std::cout << "#HB Did not pass collision check! Please check!" << std::endl; return -1;}
    
    ngHEMappingAlgorithm myngHEMappingAlgorithm;
    myngHEMappingAlgorithm.ConstructngHELMapObject("Normal");
    myngHEMappingAlgorithm.ConstructngHELMapObject("Calib");
    passCollisionCheck = myHCALLMapChecker.checkngHELMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
    if( passCollisionCheck ){ std::cout << "#HE Map pass collision check, Good!" << std::endl; }
    else{ std::cout << "#HE Did not pass collision check! Please check!" << std::endl; return -1;}

    myHCALLMapDumper.printngHBHEUMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower, myngHBMappingAlgorithm.myngHBTriggerTowerFiber,
                                           myngHBMappingAlgorithm.myngHBCalib,
                                           myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower,
                                           myngHEMappingAlgorithm.myngHECalib
    );
    myHCALLMapDumper.makedbngHBHEUMapObject("officialMap/HCALLogicalMap.db", "ngHBHEUniversalMap",
                                           myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower, myngHBMappingAlgorithm.myngHBTriggerTowerFiber,
                                           myngHBMappingAlgorithm.myngHBCalib,
                                           myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower,
                                           myngHEMappingAlgorithm.myngHECalib
    );
  }
  else if ( RunMode == "HBHEUMapCalib" )
  {
    ngHBMappingAlgorithm myngHBMappingAlgorithm;
    myngHBMappingAlgorithm.ConstructngHBLMapObject("Normal");
    myngHBMappingAlgorithm.ConstructngHBLMapObject("Calib");
    bool passCollisionCheck = myHCALLMapChecker.checkngHBLMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);
    if( passCollisionCheck ){ std::cout << "#HB Map pass collision check, Good!" << std::endl; }
    else{ std::cout << "#HB Did not pass collision check! Please check!" << std::endl; return -1;}
    
    ngHEMappingAlgorithm myngHEMappingAlgorithm;
    myngHEMappingAlgorithm.ConstructngHELMapObject("Normal");
    myngHEMappingAlgorithm.ConstructngHELMapObject("Calib");
    passCollisionCheck = myHCALLMapChecker.checkngHELMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
    if( passCollisionCheck ){ std::cout << "#HE Map pass collision check, Good!" << std::endl; }
    else{ std::cout << "#HE Did not pass collision check! Please check!" << std::endl; return -1;}

    myHCALLMapDumper.printngHBHEUMapCalibObject(myngHBMappingAlgorithm.myngHBCalib,myngHEMappingAlgorithm.myngHECalib);
  }
  else if( RunMode == "HBHEPedLMap" )
  {
    ngHBMappingAlgorithm myngHBMappingAlgorithm;
    myngHBMappingAlgorithm.ConstructngHBLMapObject("Normal");
    myngHBMappingAlgorithm.ConstructngHBLMapObject("Calib");
    bool passCollisionCheck = myHCALLMapChecker.checkngHBLMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);
    if( passCollisionCheck ){ std::cout << "#HB Map pass collision check, Good!" << std::endl; }
    else{ std::cout << "#HB Did not pass collision check! Please check!" << std::endl; return -1;}
    
    ngHEMappingAlgorithm myngHEMappingAlgorithm;
    myngHEMappingAlgorithm.ConstructngHELMapObject("Normal");
    myngHEMappingAlgorithm.ConstructngHELMapObject("Calib");
    passCollisionCheck = myHCALLMapChecker.checkngHELMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
    if( passCollisionCheck ){ std::cout << "#HE Map pass collision check, Good!" << std::endl; }
    else{ std::cout << "#HE Did not pass collision check! Please check!" << std::endl; return -1;}
    
    myHCALLMapDumper.printngHBHEPedLMapObject(myngHBMappingAlgorithm.myngHBCalib,myngHEMappingAlgorithm.myngHECalib);
  }
  else if( RunMode == "HBHELMapCalib" )
  {
    ngHBMappingAlgorithm myngHBMappingAlgorithm;
    myngHBMappingAlgorithm.ConstructngHBLMapObject("Normal");
    myngHBMappingAlgorithm.ConstructngHBLMapObject("Calib");
    bool passCollisionCheck = myHCALLMapChecker.checkngHBLMapObject(myngHBMappingAlgorithm.myngHBFrontEnd, myngHBMappingAlgorithm.myngHBBackEnd, myngHBMappingAlgorithm.myngHBSiPM, myngHBMappingAlgorithm.myngHBGeometry, myngHBMappingAlgorithm.myngHBTriggerTower);
    if( passCollisionCheck ){ std::cout << "#HB Map pass collision check, Good!" << std::endl; }
    else{ std::cout << "#HB Did not pass collision check! Please check!" << std::endl; return -1;}
    
    ngHEMappingAlgorithm myngHEMappingAlgorithm;
    myngHEMappingAlgorithm.ConstructngHELMapObject("Normal");
    myngHEMappingAlgorithm.ConstructngHELMapObject("Calib");
    passCollisionCheck = myHCALLMapChecker.checkngHELMapObject(myngHEMappingAlgorithm.myngHEFrontEnd, myngHEMappingAlgorithm.myngHEBackEnd, myngHEMappingAlgorithm.myngHESiPM, myngHEMappingAlgorithm.myngHEGeometry, myngHEMappingAlgorithm.myngHETriggerTower);
    if( passCollisionCheck ){ std::cout << "#HE Map pass collision check, Good!" << std::endl; }
    else{ std::cout << "#HE Did not pass collision check! Please check!" << std::endl; return -1;}
    
    myHCALLMapDumper.printngHBCalibLMapObject(myngHBMappingAlgorithm.myngHBCalib);
    myHCALLMapDumper.printngHECalibLMapObject(myngHEMappingAlgorithm.myngHECalib, 0);
    
  }

  else{ std::cout << "#Invalide Run Mode, what the the fuck is going on!" << std::endl; return -1; }
  return 0;
}
