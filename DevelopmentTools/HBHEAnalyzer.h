#include <vector>
#include <string>
#include <iostream>

#include "TH2D.h"
#include "TCanvas.h"
#include "TPad.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TStyle.h"

#include "HBHEMappingObject.h"

namespace HBHEAnalyzer
{
  // channels in HB
  const int NchHBHE_all = 2592+2592;
  //Front End variables
  //rbx in HB, 18 for each side
  const int NrbxHB = 18; const int NrbxHE = 18;
  //4 rm in all HB rbx, label from 1 to 4
  const int NrmHB = 4; const int NrmHE = 4;
  //rm fiber 2,3,4,5,6,7, in total 6 fibers per rm
  const int Nrm_fiber = 6;
  //fiber channel is same for both backend electronics and front end electronics, 0,1,2(since software people like start from 0)
  const int Nfiber_ch = 3;

  const int Nqie = 3;
  const int Nqie_ch = 6;

  //Back End variables
  //9 crate in HBHE: 0,1,4,5,10,11,14,15,17
  const int Ncrate = 9;
  //12 htr in each crate, 2,3,4,5,6,7 and 13,14,15,16,17,18; 12 uhtr in each crate, 1,2,3,4,5,6,7,8,9,10,11,12
  const int Nhtr = 12; const int Nuhtr = 12;
  //2 fpga flavors top and bottom in htr, while only uHTR in u
  const int Nfpga = 2; const int Nufpga = 1;
  //8 fibers per htr card: 1,2,3,4,5,6,7,8, while 12 in uhtr: 2,3,4,5,6,7,8,9 and 14,15,16,17,18,19,20,21
  const int Nhtr_fiber = 8; const int Nuhtr_fiber = 16;

  //Geometry variables in HB: 
  const int NHBHEside = 2;
  const int NHBHEphi = 72;

  const int NHBeta1516 = 2; const int NHBeta1to14 = 14;
  const int NHBdeptheta1516 = 2; const int NHBdeptheta1to14 = 1;

  const char *HBMRBXlabel[NrbxHB*NrmHB] = {"HBM01RM1","HBM01RM2","HBM01RM3","HBM01RM4",
                                           "HBM02RM1","HBM02RM2","HBM02RM3","HBM02RM4",
                                           "HBM03RM1","HBM03RM2","HBM03RM3","HBM03RM4",
                                           "HBM04RM1","HBM04RM2","HBM04RM3","HBM04RM4",
                                           "HBM05RM1","HBM05RM2","HBM05RM3","HBM05RM4",
                                           "HBM06RM1","HBM06RM2","HBM06RM3","HBM06RM4",
                                           "HBM07RM1","HBM07RM2","HBM07RM3","HBM07RM4",
                                           "HBM08RM1","HBM08RM2","HBM08RM3","HBM08RM4",
                                           "HBM09RM1","HBM09RM2","HBM09RM3","HBM09RM4",
                                           "HBM10RM1","HBM10RM2","HBM10RM3","HBM10RM4",
                                           "HBM11RM1","HBM11RM2","HBM11RM3","HBM11RM4",
                                           "HBM12RM1","HBM12RM2","HBM12RM3","HBM12RM4",
                                           "HBM13RM1","HBM13RM2","HBM13RM3","HBM13RM4",
                                           "HBM14RM1","HBM14RM2","HBM14RM3","HBM14RM4",
                                           "HBM15RM1","HBM15RM2","HBM15RM3","HBM15RM4",
                                           "HBM16RM1","HBM16RM2","HBM16RM3","HBM16RM4",
                                           "HBM17RM1","HBM17RM2","HBM17RM3","HBM17RM4",
                                           "HBM18RM1","HBM18RM2","HBM18RM3","HBM18RM4"};

  const char *HBPRBXlabel[NrbxHB*NrmHB] = {"HBP01RM1","HBP01RM2","HBP01RM3","HBP01RM4",
                                           "HBP02RM1","HBP02RM2","HBP02RM3","HBP02RM4",
                                           "HBP03RM1","HBP03RM2","HBP03RM3","HBP03RM4",
                                           "HBP04RM1","HBP04RM2","HBP04RM3","HBP04RM4",
                                           "HBP05RM1","HBP05RM2","HBP05RM3","HBP05RM4",
                                           "HBP06RM1","HBP06RM2","HBP06RM3","HBP06RM4",
                                           "HBP07RM1","HBP07RM2","HBP07RM3","HBP07RM4",
                                           "HBP08RM1","HBP08RM2","HBP08RM3","HBP08RM4",
                                           "HBP09RM1","HBP09RM2","HBP09RM3","HBP09RM4",
                                           "HBP10RM1","HBP10RM2","HBP10RM3","HBP10RM4",
                                           "HBP11RM1","HBP11RM2","HBP11RM3","HBP11RM4",
                                           "HBP12RM1","HBP12RM2","HBP12RM3","HBP12RM4",
                                           "HBP13RM1","HBP13RM2","HBP13RM3","HBP13RM4",
                                           "HBP14RM1","HBP14RM2","HBP14RM3","HBP14RM4",
                                           "HBP15RM1","HBP15RM2","HBP15RM3","HBP15RM4",
                                           "HBP16RM1","HBP16RM2","HBP16RM3","HBP16RM4",
                                           "HBP17RM1","HBP17RM2","HBP17RM3","HBP17RM4",
                                           "HBP18RM1","HBP18RM2","HBP18RM3","HBP18RM4"};

  const char *HEMRBXlabel[NrbxHE*NrmHE] = {"HEM01RM1","HEM01RM2","HEM01RM3","HEM01RM4",
                                           "HEM02RM1","HEM02RM2","HEM02RM3","HEM02RM4",
                                           "HEM03RM1","HEM03RM2","HEM03RM3","HEM03RM4",
                                           "HEM04RM1","HEM04RM2","HEM04RM3","HEM04RM4",
                                           "HEM05RM1","HEM05RM2","HEM05RM3","HEM05RM4",
                                           "HEM06RM1","HEM06RM2","HEM06RM3","HEM06RM4",
                                           "HEM07RM1","HEM07RM2","HEM07RM3","HEM07RM4",
                                           "HEM08RM1","HEM08RM2","HEM08RM3","HEM08RM4",
                                           "HEM09RM1","HEM09RM2","HEM09RM3","HEM09RM4",
                                           "HEM10RM1","HEM10RM2","HEM10RM3","HEM10RM4",
                                           "HEM11RM1","HEM11RM2","HEM11RM3","HEM11RM4",
                                           "HEM12RM1","HEM12RM2","HEM12RM3","HEM12RM4",
                                           "HEM13RM1","HEM13RM2","HEM13RM3","HEM13RM4",
                                           "HEM14RM1","HEM14RM2","HEM14RM3","HEM14RM4",
                                           "HEM15RM1","HEM15RM2","HEM15RM3","HEM15RM4",
                                           "HEM16RM1","HEM16RM2","HEM16RM3","HEM16RM4",
                                           "HEM17RM1","HEM17RM2","HEM17RM3","HEM17RM4",
                                           "HEM18RM1","HEM18RM2","HEM18RM3","HEM18RM4"};

  const char *HEPRBXlabel[NrbxHE*NrmHE] = {"HEP01RM1","HEP01RM2","HEP01RM3","HEP01RM4",
                                           "HEP02RM1","HEP02RM2","HEP02RM3","HEP02RM4",
                                           "HEP03RM1","HEP03RM2","HEP03RM3","HEP03RM4",   
                                           "HEP04RM1","HEP04RM2","HEP04RM3","HEP04RM4",   
                                           "HEP05RM1","HEP05RM2","HEP05RM3","HEP05RM4",   
                                           "HEP06RM1","HEP06RM2","HEP06RM3","HEP06RM4",   
                                           "HEP07RM1","HEP07RM2","HEP07RM3","HEP07RM4",
                                           "HEP08RM1","HEP08RM2","HEP08RM3","HEP08RM4",
                                           "HEP09RM1","HEP09RM2","HEP09RM3","HEP09RM4",
                                           "HEP10RM1","HEP10RM2","HEP10RM3","HEP10RM4",
                                           "HEP11RM1","HEP11RM2","HEP11RM3","HEP11RM4",
                                           "HEP12RM1","HEP12RM2","HEP12RM3","HEP12RM4",
                                           "HEP13RM1","HEP13RM2","HEP13RM3","HEP13RM4",
                                           "HEP14RM1","HEP14RM2","HEP14RM3","HEP14RM4",
                                           "HEP15RM1","HEP15RM2","HEP15RM3","HEP15RM4",
                                           "HEP16RM1","HEP16RM2","HEP16RM3","HEP16RM4",
                                           "HEP17RM1","HEP17RM2","HEP17RM3","HEP17RM4",
                                           "HEP18RM1","HEP18RM2","HEP18RM3","HEP18RM4"};

  const char *HBHERMfiberlabel[Nrm_fiber*Nfiber_ch] = {"RMFI2FICH0"     ,"RMFI2FICH1"     ,"RMFI2FICH2",
                                                       "RMFI3FICH0"     ,"RMFI3FICH1"     ,"RMFI3FICH2",
                                                       "RMFI4FICH0"     ,"RMFI4FICH1"     ,"RMFI4FICH2",
                                                       "RMFI5FICH0"     ,"RMFI5FICH1"     ,"RMFI5FICH2",
                                                       "RMFI6FICH0"     ,"RMFI6FICH1"     ,"RMFI6FICH2",
                                                       "RMFI7FICH0"     ,"RMFI7FICH1"     ,"RMFI7FICH2"};
  //the target directory for output plots
  std::string dir = "LMapvalidationPlots/";

  void HBHENChannelBasicCheck();
  void PlottingHBFEtoGeo(
                         std::vector<HBFrontEnd> myHBFrontEnd,
                         std::vector<HBGeometry> myHBGeometry
                        );
  void PlottingHEFEtoGeo(
                         std::vector<HEFrontEnd> myHEFrontEnd,
                         std::vector<HEGeometry> myHEGeometry
                        );
  
  void PlottingHBFEtoBEVME(
                           std::vector<HBFrontEnd> myHBFrontEnd,
                           std::vector<HBBackEnd> myHBBackEnd
                          );
  void PlottingHEFEtoBEVME(
                           std::vector<HEFrontEnd> myHEFrontEnd,
                           std::vector<HEBackEnd> myHEBackEnd
                          );
  void PlottingHBFEtoBEuTCA(
                            std::vector<HBFrontEnd> myHBFrontEnd,
                            std::vector<HBBackEnd> myHBBackEnd
                           );
  void PlottingHEFEtoBEuTCA(
                            std::vector<HEFrontEnd> myHEFrontEnd,
                            std::vector<HEBackEnd> myHEBackEnd
                           );
}

void HBHEAnalyzer::HBHENChannelBasicCheck()
{
  std::cout << "How many Channels do we have in HBHE ? " << NchHBHE_all << std::endl;
  std::cout << "Re-calculate from Front End: " << 2 * (NrbxHB * NrmHB + NrbxHE * NrmHE) * Nrm_fiber * Nfiber_ch << std::endl;
  std::cout << "Re-calculate from Back End(VME): " << Ncrate * Nhtr * Nfpga * Nhtr_fiber * Nfiber_ch << std::endl;
  std::cout << "Re-calculate from Back End(uTCA): " << Ncrate * Nuhtr * Nufpga * Nuhtr_fiber * Nfiber_ch << std::endl;
  //std::cout << "Re-calculate from Geometry: " << NHBHEside * (NHBeta1to14 * NHBdeptheta1to14 + NHBeta1516 * NHBdeptheta1516 + ) * NHBHEphi << std::endl;
  return ;
}

void HBHEAnalyzer::PlottingHBFEtoGeo(
                                     std::vector<HBFrontEnd> myHBFrontEnd,
                                     std::vector<HBGeometry> myHBGeometry
                                    )
{
  TCanvas *c = new TCanvas("c", "",0,51,4500,6000);
  c->Divide(3,2); c->SetFillColor(0); c->cd();

  TH2D *hbprbxphi = new TH2D("hbprbxphi", "Phi in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbprbxeta = new TH2D("hbprbxeta", "Eta in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbprbxdep = new TH2D("hbprbxdep", "Dep in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);

  TH2D *hbmrbxphi = new TH2D("hbmrbxphi", "Phi in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxeta = new TH2D("hbmrbxeta", "Eta in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxdep = new TH2D("hbmrbxdep", "Dep in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);

  for(auto i=0; i<(NchHBHE_all/2); i++)
  {
    std::string thisrbx = (myHBFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zphi = (myHBGeometry.at(i)).phi;
    double zeta = (myHBGeometry.at(i)).side * (myHBGeometry.at(i)).eta;
    double zdepth = (myHBGeometry.at(i)).depth;

    double x = ((myHBFrontEnd.at(i)).rm_fiber-2)*3 + (myHBFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,....18
    double rmid = (myHBFrontEnd.at(i)).rm;
    double y = (rbxid-1)*4 + rmid;

    if( thisrbx.find("HBP") != std::string::npos ){ hbprbxphi->Fill(x,y,zphi); hbprbxeta->Fill(x,y,zeta); hbprbxdep->Fill(x,y,zdepth); }
    else if( thisrbx.find("HBM") != std::string::npos ){ hbmrbxphi->Fill(x,y,zphi); hbmrbxeta->Fill(x,y,zeta); hbmrbxdep->Fill(x,y,zdepth); }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    hbprbxphi->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbprbxeta->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbprbxdep->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
    hbmrbxphi->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbmrbxeta->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbmrbxdep->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxHB*NrmHB;i++) 
  { 
    hbprbxphi->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]); hbprbxeta->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]); hbprbxdep->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]);
    hbmrbxphi->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]); hbmrbxeta->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]); hbmrbxdep->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]);
  }

  hbprbxphi->SetStats(0); hbprbxeta->SetStats(0); hbprbxdep->SetStats(0);
  hbmrbxphi->SetStats(0); hbmrbxeta->SetStats(0); hbmrbxdep->SetStats(0);

  c->cd(1); hbprbxphi->Draw("colztext"); c->cd(2); hbprbxeta->Draw("colztext"); c->cd(3); hbprbxdep->Draw("colztext");
  c->cd(4); hbmrbxphi->Draw("colztext"); c->cd(5); hbmrbxeta->Draw("colztext"); c->cd(6); hbmrbxdep->Draw("colztext");

  //title->Draw("same");

  c->SaveAs( (dir+"_HBFEetaphidepth.png").c_str() );
  c->SaveAs( (dir+"_HBFEetaphidepth.pdf").c_str() );
  c->SaveAs( (dir+"_HBFEetaphidepth.C").c_str() );
  c->Close();

  return ;
}

void HBHEAnalyzer::PlottingHEFEtoGeo(
                                     std::vector<HEFrontEnd> myHEFrontEnd,
                                     std::vector<HEGeometry> myHEGeometry
                                    )
{
  TCanvas *c = new TCanvas("c", "",0,51,4500,6000);
  c->Divide(3,2); c->SetFillColor(0); c->cd();

  TH2D *heprbxphi = new TH2D("heprbxphi", "Phi in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *heprbxeta = new TH2D("heprbxeta", "Eta in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *heprbxdep = new TH2D("heprbxdep", "Dep in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);

  TH2D *hemrbxphi = new TH2D("hemrbxphi", "Phi in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxeta = new TH2D("hemrbxeta", "Eta in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxdep = new TH2D("hemrbxdep", "Dep in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);

  for(auto i=0; i<(NchHBHE_all/2); i++)
  {
    std::string thisrbx = (myHEFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zphi = (myHEGeometry.at(i)).phi;
    double zeta = (myHEGeometry.at(i)).side * (myHEGeometry.at(i)).eta;
    double zdepth = (myHEGeometry.at(i)).depth;

    double x = ((myHEFrontEnd.at(i)).rm_fiber-2)*3 + (myHEFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,....18
    double rmid = (myHEFrontEnd.at(i)).rm;
    double y = (rbxid-1)*4 + rmid;

    if( thisrbx.find("HEP") != std::string::npos ){ heprbxphi->Fill(x,y,zphi); heprbxeta->Fill(x,y,zeta); heprbxdep->Fill(x,y,zdepth); }
    else if( thisrbx.find("HEM") != std::string::npos ){ hemrbxphi->Fill(x,y,zphi); hemrbxeta->Fill(x,y,zeta); hemrbxdep->Fill(x,y,zdepth); }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    heprbxphi->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); heprbxeta->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); heprbxdep->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
    hemrbxphi->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hemrbxeta->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hemrbxdep->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxHE*NrmHE;i++) 
  { 
    heprbxphi->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]); heprbxeta->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]); heprbxdep->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]);
    hemrbxphi->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]); hemrbxeta->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]); hemrbxdep->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]);
  }

  heprbxphi->SetStats(0); heprbxeta->SetStats(0); heprbxdep->SetStats(0);
  hemrbxphi->SetStats(0); hemrbxeta->SetStats(0); hemrbxdep->SetStats(0);

  c->cd(1); heprbxphi->Draw("colztext"); c->cd(2); heprbxeta->Draw("colztext"); c->cd(3); heprbxdep->Draw("colztext");
  c->cd(4); hemrbxphi->Draw("colztext"); c->cd(5); hemrbxeta->Draw("colztext"); c->cd(6); hemrbxdep->Draw("colztext");

  //title->Draw("same");

  c->SaveAs( (dir+"_HEFEetaphidepth.png").c_str() );
  c->SaveAs( (dir+"_HEFEetaphidepth.pdf").c_str() );
  c->SaveAs( (dir+"_HEFEetaphidepth.C").c_str() );
  c->Close();

  return ;
}

void HBHEAnalyzer::PlottingHBFEtoBEVME(
                                       std::vector<HBFrontEnd> myHBFrontEnd,
                                       std::vector<HBBackEnd> myHBBackEnd
                                      )
{
  TCanvas *c = new TCanvas("c", "",0,51,6000,6000);
  c->Divide(4,2); c->SetFillColor(0); c->cd();

  TH2D *hbprbxcrate = new TH2D("hbprbxcrate", "Crate in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbprbxhtr = new TH2D("hbprbxhtr", "HTR in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbprbxfpga = new TH2D("hbprbxfpga", "FPGA in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbprbxhtr_fiber = new TH2D("hbprbxhtr_fiber", "HTRfiber in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxcrate = new TH2D("hbmrbxcrate", "Crate in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxhtr = new TH2D("hbmrbxhtr", "HTR in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxfpga = new TH2D("hbmrbxfpga", "FPGA in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxhtr_fiber = new TH2D("hbmrbxhtr_fiber", "HTRfiber in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);

  for(auto i=0; i<NchHBHE_all/2; i++)
  {
    std::string thisrbx = (myHBFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zcrate = (myHBBackEnd.at(i)).crate;
    double zhtr = (myHBBackEnd.at(i)).htr;
    double zfpga = 2000;
    ((myHBBackEnd.at(i)).fpga)=="top" ? zfpga = 1 : zfpga = -1;
    double zhtr_fiber = (myHBBackEnd.at(i)).htr_fiber;

    double x = ((myHBFrontEnd.at(i)).rm_fiber-2)*3 + (myHBFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,2,....18
    double rmid = (myHBFrontEnd.at(i)).rm;
    double y = (rbxid-1)*4 + rmid;
    
    if( thisrbx.find("HBP") != std::string::npos ){ hbprbxcrate->Fill(x,y,zcrate); hbprbxhtr->Fill(x,y,zhtr); hbprbxfpga->Fill(x,y,zfpga); hbprbxhtr_fiber->Fill(x,y,zhtr_fiber); }
    else if( thisrbx.find("HBM") != std::string::npos ){ hbmrbxcrate->Fill(x,y,zcrate); hbmrbxhtr->Fill(x,y,zhtr); hbmrbxfpga->Fill(x,y,zfpga); hbmrbxhtr_fiber->Fill(x,y,zhtr_fiber); }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    hbprbxcrate->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbprbxhtr->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); 
    hbprbxfpga->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbprbxhtr_fiber->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);

    hbmrbxcrate->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbmrbxhtr->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
    hbmrbxfpga->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbmrbxhtr_fiber->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxHB*NrmHB;i++) 
  { 
    hbprbxcrate->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]); hbprbxhtr->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]); 
    hbprbxfpga->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]); hbprbxhtr_fiber->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]);
    
    hbmrbxcrate->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]); hbmrbxhtr->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]);
    hbmrbxfpga->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]); hbmrbxhtr_fiber->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]);
  }

  hbprbxcrate->SetStats(0); hbprbxhtr->SetStats(0); hbprbxfpga->SetStats(0); hbprbxhtr_fiber->SetStats(0);
  hbmrbxcrate->SetStats(0); hbmrbxhtr->SetStats(0); hbmrbxfpga->SetStats(0); hbmrbxhtr_fiber->SetStats(0);

  c->cd(1); hbprbxcrate->Draw("colztext"); c->cd(2); hbprbxhtr->Draw("colztext"); c->cd(3); hbprbxfpga->Draw("colztext"); c->cd(4); hbprbxhtr_fiber->Draw("colztext");
  c->cd(5); hbmrbxcrate->Draw("colztext"); c->cd(6); hbmrbxhtr->Draw("colztext"); c->cd(7); hbmrbxfpga->Draw("colztext"); c->cd(8); hbmrbxhtr_fiber->Draw("colztext");

  c->SaveAs( (dir+"_HBFEcratehtrfpgahtr_fiber.png").c_str() );
  c->SaveAs( (dir+"_HBFEcratehtrfpgahtr_fiber.pdf").c_str() );
  c->SaveAs( (dir+"_HBFEcratehtrfpgahtr_fiber.C").c_str() );
  c->Close();

  return ;
}

void HBHEAnalyzer::PlottingHEFEtoBEVME(
                                       std::vector<HEFrontEnd> myHEFrontEnd,
                                       std::vector<HEBackEnd> myHEBackEnd
                                      )
{
  TCanvas *c = new TCanvas("c", "",0,51,6000,6000);
  c->Divide(4,2); c->SetFillColor(0); c->cd();

  TH2D *heprbxcrate = new TH2D("heprbxcrate", "Crate in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *heprbxhtr = new TH2D("heprbxhtr", "HTR in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *heprbxfpga = new TH2D("heprbxfpga", "FPGA in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *heprbxhtr_fiber = new TH2D("heprbxhtr_fiber", "HTRfiber in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxcrate = new TH2D("hemrbxcrate", "Crate in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxhtr = new TH2D("hemrbxhtr", "HTR in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxfpga = new TH2D("hemrbxfpga", "FPGA in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxhtr_fiber = new TH2D("hemrbxhtr_fiber", "HTRfiber in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);

  for(auto i=0; i<NchHBHE_all/2; i++)
  {
    std::string thisrbx = (myHEFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zcrate = (myHEBackEnd.at(i)).crate;
    double zhtr = (myHEBackEnd.at(i)).htr;
    double zfpga = 2000;
    ((myHEBackEnd.at(i)).fpga)=="top" ? zfpga = 1 : zfpga = -1;
    double zhtr_fiber = (myHEBackEnd.at(i)).htr_fiber;

    double x = ((myHEFrontEnd.at(i)).rm_fiber-2)*3 + (myHEFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,....18
    double rmid = (myHEFrontEnd.at(i)).rm;
    double y = (rbxid-1)*4 + rmid;
    
    if( thisrbx.find("HEP") != std::string::npos ){ heprbxcrate->Fill(x,y,zcrate); heprbxhtr->Fill(x,y,zhtr); heprbxfpga->Fill(x,y,zfpga); heprbxhtr_fiber->Fill(x,y,zhtr_fiber); }
    else if( thisrbx.find("HEM") != std::string::npos ){ hemrbxcrate->Fill(x,y,zcrate); hemrbxhtr->Fill(x,y,zhtr); hemrbxfpga->Fill(x,y,zfpga); hemrbxhtr_fiber->Fill(x,y,zhtr_fiber); }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    heprbxcrate->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); heprbxhtr->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); 
    heprbxfpga->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); heprbxhtr_fiber->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);

    hemrbxcrate->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hemrbxhtr->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
    hemrbxfpga->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hemrbxhtr_fiber->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxHE*NrmHE;i++) 
  { 
    heprbxcrate->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]); heprbxhtr->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]); 
    heprbxfpga->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]); heprbxhtr_fiber->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]);
    
    hemrbxcrate->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]); hemrbxhtr->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]);
    hemrbxfpga->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]); hemrbxhtr_fiber->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]);
  }

  heprbxcrate->SetStats(0); heprbxhtr->SetStats(0); heprbxfpga->SetStats(0); heprbxhtr_fiber->SetStats(0);
  hemrbxcrate->SetStats(0); hemrbxhtr->SetStats(0); hemrbxfpga->SetStats(0); hemrbxhtr_fiber->SetStats(0);

  c->cd(1); heprbxcrate->Draw("colztext"); c->cd(2); heprbxhtr->Draw("colztext"); c->cd(3); heprbxfpga->Draw("colztext"); c->cd(4); heprbxhtr_fiber->Draw("colztext");
  c->cd(5); hemrbxcrate->Draw("colztext"); c->cd(6); hemrbxhtr->Draw("colztext"); c->cd(7); hemrbxfpga->Draw("colztext"); c->cd(8); hemrbxhtr_fiber->Draw("colztext");

  c->SaveAs( (dir+"_HEFEcratehtrfpgahtr_fiber.png").c_str() );
  c->SaveAs( (dir+"_HEFEcratehtrfpgahtr_fiber.pdf").c_str() );
  c->SaveAs( (dir+"_HEFEcratehtrfpgahtr_fiber.C").c_str() );
  c->Close();

  return ;
}

void HBHEAnalyzer::PlottingHBFEtoBEuTCA(
                                        std::vector<HBFrontEnd> myHBFrontEnd,
                                        std::vector<HBBackEnd> myHBBackEnd
                                       )
{
  TCanvas *c = new TCanvas("c", "",0,51,6000,6000);
  c->Divide(4,2); c->SetFillColor(0); c->cd();

  TH2D *hbprbxucrate = new TH2D("hbprbxucrate", "Crate in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbprbxuhtr = new TH2D("hbprbxuhtr", "HTR in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbprbxufpga = new TH2D("hbprbxufpga", "FPGA in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbprbxuhtr_fiber = new TH2D("hbprbxuhtr_fiber", "HTRfiber in HBP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxucrate = new TH2D("hbmrbxucrate", "Crate in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxuhtr = new TH2D("hbmrbxuhtr", "HTR in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxufpga = new TH2D("hbmrbxufpga", "FPGA in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);
  TH2D *hbmrbxuhtr_fiber = new TH2D("hbmrbxuhtr_fiber", "HTRfiber in HBM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHB*NrmHB, 1, NrbxHB*NrmHB+1);

  for(auto i=0; i<NchHBHE_all/2; i++)
  {
    std::string thisrbx = (myHBFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zucrate = (myHBBackEnd.at(i)).ucrate;
    double zuhtr = (myHBBackEnd.at(i)).uhtr;
    double zufpga = 2000;
    ((myHBBackEnd.at(i)).ufpga)=="uHTR" ? zufpga = 10 : zufpga = -10;
    double zuhtr_fiber = (myHBBackEnd.at(i)).uhtr_fiber;

    double x = ((myHBFrontEnd.at(i)).rm_fiber-2)*3 + (myHBFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,2,....18
    double rmid = (myHBFrontEnd.at(i)).rm;
    double y = (rbxid-1)*4 + rmid;
    
    if( thisrbx.find("HBP") != std::string::npos ){ hbprbxucrate->Fill(x,y,zucrate); hbprbxuhtr->Fill(x,y,zuhtr); hbprbxufpga->Fill(x,y,zufpga); hbprbxuhtr_fiber->Fill(x,y,zuhtr_fiber); }
    else if( thisrbx.find("HBM") != std::string::npos ){ hbmrbxucrate->Fill(x,y,zucrate); hbmrbxuhtr->Fill(x,y,zuhtr); hbmrbxufpga->Fill(x,y,zufpga); hbmrbxuhtr_fiber->Fill(x,y,zuhtr_fiber); }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    hbprbxucrate->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbprbxuhtr->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); 
    hbprbxufpga->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbprbxuhtr_fiber->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);

    hbmrbxucrate->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbmrbxuhtr->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
    hbmrbxufpga->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hbmrbxuhtr_fiber->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxHB*NrmHB;i++) 
  { 
    hbprbxucrate->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]); hbprbxuhtr->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]); 
    hbprbxufpga->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]); hbprbxuhtr_fiber->GetYaxis()->SetBinLabel(i,HBPRBXlabel[i-1]);
    
    hbmrbxucrate->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]); hbmrbxuhtr->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]);
    hbmrbxufpga->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]); hbmrbxuhtr_fiber->GetYaxis()->SetBinLabel(i,HBMRBXlabel[i-1]);
  }

  hbprbxucrate->SetStats(0); hbprbxuhtr->SetStats(0); hbprbxufpga->SetStats(0); hbprbxuhtr_fiber->SetStats(0);
  hbmrbxucrate->SetStats(0); hbmrbxuhtr->SetStats(0); hbmrbxufpga->SetStats(0); hbmrbxuhtr_fiber->SetStats(0);

  c->cd(1); hbprbxucrate->Draw("colztext"); c->cd(2); hbprbxuhtr->Draw("colztext"); c->cd(3); hbprbxufpga->Draw("colztext"); c->cd(4); hbprbxuhtr_fiber->Draw("colztext");
  c->cd(5); hbmrbxucrate->Draw("colztext"); c->cd(6); hbmrbxuhtr->Draw("colztext"); c->cd(7); hbmrbxufpga->Draw("colztext"); c->cd(8); hbmrbxuhtr_fiber->Draw("colztext");

  c->SaveAs( (dir+"_HBFEucrateuhtrufpgauhtr_fiber.png").c_str() );
  c->SaveAs( (dir+"_HBFEucrateuhtrufpgauhtr_fiber.pdf").c_str() );
  c->SaveAs( (dir+"_HBFEucrateuhtrufpgauhtr_fiber.C").c_str() );
  c->Close();

  return ;
}

void HBHEAnalyzer::PlottingHEFEtoBEuTCA(
                                        std::vector<HEFrontEnd> myHEFrontEnd,
                                        std::vector<HEBackEnd> myHEBackEnd
                                       )
{
  TCanvas *c = new TCanvas("c", "",0,51,6000,6000);
  c->Divide(4,2); c->SetFillColor(0); c->cd();

  TH2D *heprbxucrate = new TH2D("heprbxucrate", "Crate in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *heprbxuhtr = new TH2D("heprbxuhtr", "HTR in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *heprbxufpga = new TH2D("heprbxufpga", "FPGA in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *heprbxuhtr_fiber = new TH2D("heprbxuhtr_fiber", "HTRfiber in HEP FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxucrate = new TH2D("hemrbxucrate", "Crate in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxuhtr = new TH2D("hemrbxuhtr", "HTR in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxufpga = new TH2D("hemrbxufpga", "FPGA in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);
  TH2D *hemrbxuhtr_fiber = new TH2D("hemrbxuhtr_fiber", "HTRfiber in HEM FrontEnd", Nrm_fiber*Nfiber_ch, 1, Nrm_fiber*Nfiber_ch+1, NrbxHE*NrmHE, 1, NrbxHE*NrmHE+1);

  for(auto i=0; i<NchHBHE_all/2; i++)
  {
    std::string thisrbx = (myHEFrontEnd.at(i)).rbx;
    //std::cout << thisrbx << std::endl;
    double zucrate = (myHEBackEnd.at(i)).ucrate;
    double zuhtr = (myHEBackEnd.at(i)).uhtr;
    double zufpga = 2000;
    ((myHEBackEnd.at(i)).ufpga)=="uHTR" ? zufpga = 10 : zufpga = -10;
    double zuhtr_fiber = (myHEBackEnd.at(i)).uhtr_fiber;

    double x = ((myHEFrontEnd.at(i)).rm_fiber-2)*3 + (myHEFrontEnd.at(i)).fiber_ch + 1;
    double rbxid = std::stod( thisrbx.substr( thisrbx.length() - 2 ) );//1,2,....18
    double rmid = (myHEFrontEnd.at(i)).rm;
    double y = (rbxid-1)*4 + rmid;
    
    if( thisrbx.find("HEP") != std::string::npos ){ heprbxucrate->Fill(x,y,zucrate); heprbxuhtr->Fill(x,y,zuhtr); heprbxufpga->Fill(x,y,zufpga); heprbxuhtr_fiber->Fill(x,y,zuhtr_fiber); }
    else if( thisrbx.find("HEM") != std::string::npos ){ hemrbxucrate->Fill(x,y,zucrate); hemrbxuhtr->Fill(x,y,zuhtr); hemrbxufpga->Fill(x,y,zufpga); hemrbxuhtr_fiber->Fill(x,y,zuhtr_fiber); }
  }

  for(int i=1;i<=Nrm_fiber*Nfiber_ch;i++)
  { 
    heprbxucrate->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); heprbxuhtr->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); 
    heprbxufpga->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); heprbxuhtr_fiber->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);

    hemrbxucrate->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hemrbxuhtr->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
    hemrbxufpga->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]); hemrbxuhtr_fiber->GetXaxis()->SetBinLabel(i,HBHERMfiberlabel[i-1]);
  }
  for(int i=1;i<=NrbxHE*NrmHE;i++) 
  { 
    heprbxucrate->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]); heprbxuhtr->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]); 
    heprbxufpga->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]); heprbxuhtr_fiber->GetYaxis()->SetBinLabel(i,HEPRBXlabel[i-1]);
    
    hemrbxucrate->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]); hemrbxuhtr->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]);
    hemrbxufpga->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]); hemrbxuhtr_fiber->GetYaxis()->SetBinLabel(i,HEMRBXlabel[i-1]);
  }

  heprbxucrate->SetStats(0); heprbxuhtr->SetStats(0); heprbxufpga->SetStats(0); heprbxuhtr_fiber->SetStats(0);
  hemrbxucrate->SetStats(0); hemrbxuhtr->SetStats(0); hemrbxufpga->SetStats(0); hemrbxuhtr_fiber->SetStats(0);

  c->cd(1); heprbxucrate->Draw("colztext"); c->cd(2); heprbxuhtr->Draw("colztext"); c->cd(3); heprbxufpga->Draw("colztext"); c->cd(4); heprbxuhtr_fiber->Draw("colztext");
  c->cd(5); hemrbxucrate->Draw("colztext"); c->cd(6); hemrbxuhtr->Draw("colztext"); c->cd(7); hemrbxufpga->Draw("colztext"); c->cd(8); hemrbxuhtr_fiber->Draw("colztext");

  c->SaveAs( (dir+"_HEFEucrateuhtrufpgauhtr_fiber.png").c_str() );
  c->SaveAs( (dir+"_HEFEucrateuhtrufpgauhtr_fiber.pdf").c_str() );
  c->SaveAs( (dir+"_HEFEucrateuhtrufpgauhtr_fiber.C").c_str() );
  c->Close();

  return ;
}
