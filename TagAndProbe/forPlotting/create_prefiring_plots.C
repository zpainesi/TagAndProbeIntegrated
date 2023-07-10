///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////
// This script is for computing the plotting the pre-/post-firing rates for EG, Muons, Jets      //
// as a functon of eta for EG only.	 ( -> see objects cuts at the end <- )		    //
///////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////


#include <sys/stat.h>
#include <stdio.h>
#include "TCanvas.h"
#include "TH1F.h"
#include <iostream>
#include <filesystem>

void create_prefiring_plots(TString fIn, TString era)
{
TString directoryName = "../plots/"+era;
int result = mkdir(directoryName, 0777);

// Histos definition
TH1I *histo_eg_BX_cut1=new TH1I("","",5,-2.5,2.5);
TH1I *histo_mu_BX_cut1=new TH1I("","",5,-2.5,2.5);
TH1I *histo_mu_BX_cut2=new TH1I("","",5,-2.5,2.5);
TH1I *histo_jet_BX_cut1=new TH1I("","",5,-2.5,2.5);

histo_eg_BX_cut1->SetStats(0);
histo_mu_BX_cut1->SetStats(0);
histo_mu_BX_cut2->SetStats(0);
histo_jet_BX_cut1->SetStats(0);


TH1D *histo_eg_eta_cut1[5];
TH1D *histo_mu_eta_cut1[5];
TH1D *histo_mu_eta_cut2[5];
TH1D *histo_jet_eta_cut1[5]; // one for each BX
TH1D *rate_vs_eta_eg_cut1[2], *rate_vs_eta_eg_cut1_num[2], *rate_vs_eta_eg_cut1_den[2];
TH1D *rate_vs_eta_mu_cut1[2], *rate_vs_eta_mu_cut1_num[2], *rate_vs_eta_mu_cut1_den[2];
TH1D *rate_vs_eta_mu_cut2[2], *rate_vs_eta_mu_cut2_num[2], *rate_vs_eta_mu_cut2_den[2];
TH1D *rate_vs_eta_jet_cut1[2], *rate_vs_eta_jet_cut1_num[2], *rate_vs_eta_jet_cut1_den[2]; //0 for pre, 1 for post

TH2D *map_eta_phi_eg_cut1[2],*map_eta_phi_mu_cut1[2], *map_eta_phi_mu_cut2[2], *map_eta_phi_jet_cut1[2];




for(int i=0; i<5; i++)
{
	histo_eg_eta_cut1[i]=new TH1D("","",60,-3.,3.);
	histo_mu_eta_cut1[i]=new TH1D("","",100,-5.,5.);
	histo_mu_eta_cut2[i]=new TH1D("","",100,-5.,5.);
	histo_jet_eta_cut1[i]=new TH1D("","",100,-5.,5.);
	histo_eg_eta_cut1[i]->Sumw2();
	histo_mu_eta_cut1[i]->Sumw2();
	histo_mu_eta_cut2[i]->Sumw2();
	histo_jet_eta_cut1[i]->Sumw2();
	histo_eg_eta_cut1[i]->SetStats(0);
	histo_mu_eta_cut1[i]->SetStats(0);
	histo_mu_eta_cut2[i]->SetStats(0);
	histo_jet_eta_cut1[i]->SetStats(0);
	if(i<2)
	{
		rate_vs_eta_eg_cut1[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_cut1_num[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_eg_cut1_den[i]=new TH1D("","",60,-3.,3.);
		rate_vs_eta_mu_cut1[i]=new TH1D("","",100,-5.,5.);
		rate_vs_eta_mu_cut1_num[i]=new TH1D("","",100,-5.,5.);
		rate_vs_eta_mu_cut1_den[i]=new TH1D("","",100,-5.,5.);
		rate_vs_eta_mu_cut2[i]=new TH1D("","",100,-5.,5.);
		rate_vs_eta_mu_cut2_num[i]=new TH1D("","",100,-5.,5.);
		rate_vs_eta_mu_cut2_den[i]=new TH1D("","",100,-5.,5.);
		rate_vs_eta_jet_cut1[i]=new TH1D("","",100,-5.,5.);
		rate_vs_eta_jet_cut1_num[i]=new TH1D("","",100,-5.,5.);
		rate_vs_eta_jet_cut1_den[i]=new TH1D("","",100,-5.,5.);
		rate_vs_eta_eg_cut1[i]->Sumw2();
		rate_vs_eta_eg_cut1_num[i]->Sumw2();
		rate_vs_eta_eg_cut1_den[i]->Sumw2();
		rate_vs_eta_mu_cut1[i]->Sumw2();
		rate_vs_eta_mu_cut1_num[i]->Sumw2();
		rate_vs_eta_mu_cut1_den[i]->Sumw2();
		rate_vs_eta_mu_cut2[i]->Sumw2();
		rate_vs_eta_mu_cut2_num[i]->Sumw2();
		rate_vs_eta_mu_cut2_den[i]->Sumw2();
		rate_vs_eta_jet_cut1[i]->Sumw2();
		rate_vs_eta_jet_cut1_num[i]->Sumw2();
		rate_vs_eta_jet_cut1_den[i]->Sumw2();
		rate_vs_eta_eg_cut1[i]->SetStats(0);
		rate_vs_eta_eg_cut1_num[i]->SetStats(0);
		rate_vs_eta_eg_cut1_den[i]->SetStats(0);
		rate_vs_eta_mu_cut1[i]->SetStats(0);
		rate_vs_eta_mu_cut1_num[i]->SetStats(0);
		rate_vs_eta_mu_cut1_den[i]->SetStats(0);
		rate_vs_eta_mu_cut2[i]->SetStats(0);
		rate_vs_eta_mu_cut2_num[i]->SetStats(0);
		rate_vs_eta_mu_cut2_den[i]->SetStats(0);
		rate_vs_eta_jet_cut1[i]->SetStats(0);
		rate_vs_eta_jet_cut1_num[i]->SetStats(0);
		rate_vs_eta_jet_cut1_den[i]->SetStats(0);
		map_eta_phi_eg_cut1[i]=new TH2D("","",36,-3.1416,3.1416,36,-3.1416,3.1416);
		map_eta_phi_mu_cut1[i]=new TH2D("","",36,-3.1416,3.1416,36,-3.1416,3.1416);
		map_eta_phi_mu_cut2[i]=new TH2D("","",36,-3.1416,3.1416,36,-3.1416,3.1416);
		map_eta_phi_jet_cut1[i]=new TH2D("","",36,-3.1416,3.1416,36,-3.1416,3.1416);
		map_eta_phi_eg_cut1[i]->SetStats(0);
		map_eta_phi_eg_cut1[i]->GetXaxis()->SetTitle("#eta_{offl}");
		map_eta_phi_eg_cut1[i]->GetYaxis()->SetTitle("#phi_{offl}");
		map_eta_phi_eg_cut1[i]->GetYaxis()->SetTitleOffset(1.7);
		map_eta_phi_eg_cut1[i]->GetZaxis()->SetTitleOffset(1.7);
		map_eta_phi_eg_cut1[i]->GetXaxis()->SetTitleOffset(1.5);
		map_eta_phi_eg_cut1[i]->GetYaxis()->SetTitleSize(.03);
		map_eta_phi_eg_cut1[i]->GetZaxis()->SetTitleSize(.04);
		map_eta_phi_eg_cut1[i]->GetXaxis()->SetTitleSize(.03);
		map_eta_phi_mu_cut1[i]->SetStats(0);
		map_eta_phi_mu_cut1[i]->GetXaxis()->SetTitle("#eta_{offl}");
		map_eta_phi_mu_cut1[i]->GetYaxis()->SetTitle("#phi_{offl}");
		map_eta_phi_mu_cut1[i]->GetYaxis()->SetTitleOffset(1.7);
		map_eta_phi_mu_cut1[i]->GetZaxis()->SetTitleOffset(1.7);
		map_eta_phi_mu_cut1[i]->GetXaxis()->SetTitleOffset(1.5);
		map_eta_phi_mu_cut1[i]->GetYaxis()->SetTitleSize(.03);
		map_eta_phi_mu_cut1[i]->GetZaxis()->SetTitleSize(.04);
		map_eta_phi_mu_cut1[i]->GetXaxis()->SetTitleSize(.03);
		map_eta_phi_mu_cut2[i]->SetStats(0);
		map_eta_phi_mu_cut2[i]->GetXaxis()->SetTitle("#eta_{offl}");
		map_eta_phi_mu_cut2[i]->GetYaxis()->SetTitle("#phi_{offl}");
		map_eta_phi_mu_cut2[i]->GetYaxis()->SetTitleOffset(1.7);
		map_eta_phi_mu_cut2[i]->GetZaxis()->SetTitleOffset(1.7);
		map_eta_phi_mu_cut2[i]->GetXaxis()->SetTitleOffset(1.5);
		map_eta_phi_mu_cut2[i]->GetYaxis()->SetTitleSize(.03);
		map_eta_phi_mu_cut2[i]->GetZaxis()->SetTitleSize(.04);
		map_eta_phi_mu_cut2[i]->GetXaxis()->SetTitleSize(.03);
		map_eta_phi_jet_cut1[i]->SetStats(0);
		map_eta_phi_jet_cut1[i]->GetXaxis()->SetTitle("#eta_{offl}");
		map_eta_phi_jet_cut1[i]->GetYaxis()->SetTitle("#phi_{offl}");
		map_eta_phi_jet_cut1[i]->GetYaxis()->SetTitleOffset(1.7);
		map_eta_phi_jet_cut1[i]->GetZaxis()->SetTitleOffset(1.7);
		map_eta_phi_jet_cut1[i]->GetXaxis()->SetTitleOffset(1.5);
		map_eta_phi_jet_cut1[i]->GetYaxis()->SetTitleSize(.03);
		map_eta_phi_jet_cut1[i]->GetZaxis()->SetTitleSize(.04);
		map_eta_phi_jet_cut1[i]->GetXaxis()->SetTitleSize(.03);
	}
}

// Input file
TFile *fin=new TFile( fIn , "READ"); 

// Trees, branches & variables definition
TTree *EG=(TTree*)fin->Get("ZeroBias_Timing/EG");
TTree *Mu=(TTree*)fin->Get("ZeroBias_Timing/Mu");
TTree *Jet=(TTree*)fin->Get("ZeroBias_Timing/Jet");

float jetPt,jetEta, jetPhi, l1tJetPt, l1tJetEta, l1tJetPhi;
Int_t l1tJetQual, l1tJetIso,  l1tJetBx;

float egPt,egEta, egPhi, l1tEgPt, l1tEgEta, l1tEgPhi;
Int_t l1tEgQual, l1tEgIso,  l1tEgBx;

float muPt,muEta, muPhi, l1tMuPt, l1tMuEta, l1tMuPhi;
Int_t l1tMuQual, l1tMuIso,  l1tMuBx;

EG->SetBranchAddress("l1tEgPt",&l1tEgPt);
EG->SetBranchAddress("l1tEgEta",&l1tEgEta);
EG->SetBranchAddress("l1tEgPhi",&l1tEgPhi);
EG->SetBranchAddress("l1tEgQual",&l1tEgQual);
EG->SetBranchAddress("l1tEgIso",&l1tEgIso);
EG->SetBranchAddress("l1tEgBx",&l1tEgBx);
EG->SetBranchAddress("egPt",&egPt);
EG->SetBranchAddress("egEta",&egEta);
EG->SetBranchAddress("egPhi",&egPhi);

Mu->SetBranchAddress("l1tMuPt",&l1tMuPt);
Mu->SetBranchAddress("l1tMuEta",&l1tMuEta);
Mu->SetBranchAddress("l1tMuPhi",&l1tMuPhi);
Mu->SetBranchAddress("l1tMuQual",&l1tMuQual);
Mu->SetBranchAddress("l1tMuIso",&l1tMuIso);
Mu->SetBranchAddress("l1tMuBx",&l1tMuBx);
Mu->SetBranchAddress("muPt",&muPt);
Mu->SetBranchAddress("muEta",&muEta);
Mu->SetBranchAddress("muPhi",&muPhi);

Jet->SetBranchAddress("l1tJetPt",&l1tJetPt);
Jet->SetBranchAddress("l1tJetEta",&l1tJetEta);
Jet->SetBranchAddress("l1tJetPhi",&l1tJetPhi);
Jet->SetBranchAddress("l1tJetQual",&l1tJetQual);
Jet->SetBranchAddress("l1tJetIso",&l1tJetIso);
Jet->SetBranchAddress("l1tJetBx",&l1tJetBx);
Jet->SetBranchAddress("jetPt",&jetPt);
Jet->SetBranchAddress("jetEta",&jetEta);
Jet->SetBranchAddress("jetPhi",&jetPhi);


int entries_eg=EG->GetEntries();
int entries_mu=Mu->GetEntries();
int entries_jet=Jet->GetEntries();

// EG
for (int i=0; i<entries_eg; i++)
{
	EG->GetEntry(i);
	if( egPt>12. && egPt<23. && l1tEgPt>15. && l1tEgPt<26.)
	{
		histo_eg_BX_cut1->Fill(l1tEgBx,1.);
		if(l1tEgBx==-2)histo_eg_eta_cut1[0]->Fill(egEta,1.);
		if(l1tEgBx==-1)
		{
			histo_eg_eta_cut1[1]->Fill(egEta,1.);
			map_eta_phi_eg_cut1[0]->Fill(egEta,egPhi); //pre
		}
		if(l1tEgBx==0)histo_eg_eta_cut1[2]->Fill(egEta,1.);
		if(l1tEgBx==1)
		{
			histo_eg_eta_cut1[3]->Fill(egEta,1.);
			map_eta_phi_eg_cut1[1]->Fill(egEta,egPhi); //post
		}
		if(l1tEgBx==2)histo_eg_eta_cut1[4]->Fill(egEta,1.);
	}	
}
// pre
rate_vs_eta_eg_cut1_num[0]->Add(histo_eg_eta_cut1[1]);
rate_vs_eta_eg_cut1_den[0]->Add(histo_eg_eta_cut1[1]);
rate_vs_eta_eg_cut1_den[0]->Add(histo_eg_eta_cut1[2]);
rate_vs_eta_eg_cut1[0]->Divide(rate_vs_eta_eg_cut1_num[0],rate_vs_eta_eg_cut1_den[0]);

// post
rate_vs_eta_eg_cut1_num[1]->Add(histo_eg_eta_cut1[3]);
rate_vs_eta_eg_cut1_den[1]->Add(histo_eg_eta_cut1[3]);
rate_vs_eta_eg_cut1_den[1]->Add(histo_eg_eta_cut1[2]);
rate_vs_eta_eg_cut1[1]->Divide(rate_vs_eta_eg_cut1_num[1],rate_vs_eta_eg_cut1_den[1]);

// Mu 
for (int i=0; i<entries_mu; i++)
{
	Mu->GetEntry(i);
	if( muPt>8. && muPt<25. && l1tMuPt>10. && l1tMuPt<21.)
	{
		histo_mu_BX_cut1->Fill(l1tMuBx,1.);
		if(l1tMuBx==-2)histo_mu_eta_cut1[0]->Fill(muEta,1.);
		if(l1tMuBx==-1)
		{
			histo_mu_eta_cut1[1]->Fill(muEta,1.);
			map_eta_phi_mu_cut1[0]->Fill(muEta,muPhi);
		}
		if(l1tMuBx==0)histo_mu_eta_cut1[2]->Fill(muEta,1.);
		if(l1tMuBx==1)
		{
			histo_mu_eta_cut1[3]->Fill(muEta,1.);
			map_eta_phi_mu_cut1[1]->Fill(muEta,muPhi);
		}
		if(l1tMuBx==2)histo_mu_eta_cut1[4]->Fill(muEta,1.);
	}
	if( muPt>20. && l1tMuPt>22.)
	{
		histo_mu_BX_cut2->Fill(l1tMuBx,1.);
		if(l1tMuBx==-2)histo_mu_eta_cut2[0]->Fill(muEta,1.);
		if(l1tMuBx==-1)
		{
			histo_mu_eta_cut2[1]->Fill(muEta,1.);
			map_eta_phi_mu_cut2[0]->Fill(muEta,muPhi);
		}
		if(l1tMuBx==0)histo_mu_eta_cut2[2]->Fill(muEta,1.);
		if(l1tMuBx==1)
		{
			histo_mu_eta_cut2[3]->Fill(muEta,1.);
			map_eta_phi_mu_cut2[1]->Fill(muEta,muPhi);
		}
		if(l1tMuBx==2)histo_mu_eta_cut2[4]->Fill(muEta,1.);
	}	
}
// pre
rate_vs_eta_mu_cut1_num[0]->Add(histo_mu_eta_cut1[1]);
rate_vs_eta_mu_cut1_den[0]->Add(histo_mu_eta_cut1[1]);
rate_vs_eta_mu_cut1_den[0]->Add(histo_mu_eta_cut1[2]);
rate_vs_eta_mu_cut1[0]->Divide(rate_vs_eta_mu_cut1_num[0],rate_vs_eta_mu_cut1_den[0]);

// post
rate_vs_eta_mu_cut1_num[1]->Add(histo_mu_eta_cut1[3]);
rate_vs_eta_mu_cut1_den[1]->Add(histo_mu_eta_cut1[3]);
rate_vs_eta_mu_cut1_den[1]->Add(histo_mu_eta_cut1[2]);
rate_vs_eta_mu_cut1[1]->Divide(rate_vs_eta_mu_cut1_num[1],rate_vs_eta_mu_cut1_den[1]);

// pre
rate_vs_eta_mu_cut2_num[0]->Add(histo_mu_eta_cut2[1]);
rate_vs_eta_mu_cut2_den[0]->Add(histo_mu_eta_cut2[1]);
rate_vs_eta_mu_cut2_den[0]->Add(histo_mu_eta_cut2[2]);
rate_vs_eta_mu_cut2[0]->Divide(rate_vs_eta_mu_cut2_num[0],rate_vs_eta_mu_cut2_den[0]);

// post
rate_vs_eta_mu_cut2_num[1]->Add(histo_mu_eta_cut2[3]);
rate_vs_eta_mu_cut2_den[1]->Add(histo_mu_eta_cut2[3]);
rate_vs_eta_mu_cut2_den[1]->Add(histo_mu_eta_cut2[2]);
rate_vs_eta_mu_cut2[1]->Divide(rate_vs_eta_mu_cut2_num[1],rate_vs_eta_mu_cut2_den[1]);

// Jet
for (int i=0; i<entries_jet; i++)
{
	Jet->GetEntry(i);
	if( jetPt>90. && jetPt<160. && l1tJetPt>100. && l1tJetPt<150.)
	{
		histo_jet_BX_cut1->Fill(l1tJetBx,1.);
		if(l1tJetBx==-2)histo_jet_eta_cut1[0]->Fill(jetEta,1.);
		if(l1tJetBx==-1)
		{
			histo_jet_eta_cut1[1]->Fill(jetEta,1.);
			map_eta_phi_jet_cut1[0]->Fill(jetEta,jetPhi);
		}
		if(l1tJetBx==0)histo_jet_eta_cut1[2]->Fill(jetEta,1.);
		if(l1tJetBx==1)
		{
			histo_jet_eta_cut1[3]->Fill(jetEta,1.);
			map_eta_phi_jet_cut1[1]->Fill(jetEta,jetPhi);
		}
		if(l1tJetBx==2)histo_jet_eta_cut1[4]->Fill(jetEta,1.);
	}	
}
// pre
rate_vs_eta_jet_cut1_num[0]->Add(histo_jet_eta_cut1[1]);
rate_vs_eta_jet_cut1_den[0]->Add(histo_jet_eta_cut1[1]);
rate_vs_eta_jet_cut1_den[0]->Add(histo_jet_eta_cut1[2]);
rate_vs_eta_jet_cut1[0]->Divide(rate_vs_eta_jet_cut1_num[0],rate_vs_eta_jet_cut1_den[0]);

// post
rate_vs_eta_jet_cut1_num[1]->Add(histo_jet_eta_cut1[3]);
rate_vs_eta_jet_cut1_den[1]->Add(histo_jet_eta_cut1[3]);
rate_vs_eta_jet_cut1_den[1]->Add(histo_jet_eta_cut1[2]);
rate_vs_eta_jet_cut1[1]->Divide(rate_vs_eta_jet_cut1_num[1],rate_vs_eta_jet_cut1_den[1]);

// Total rates
cout <<endl<< "\033[1;33m---> For era: \033[0m" << era;
float total_eg_pre_rate_cut1=(histo_eg_BX_cut1->GetBinContent(2))/(histo_eg_BX_cut1->GetBinContent(2)+histo_eg_BX_cut1->GetBinContent(3));
cout<<endl<<"The total pre-firing rate for EG is "<<total_eg_pre_rate_cut1*100.<<"%";
float total_eg_post_rate_cut1=(histo_eg_BX_cut1->GetBinContent(4))/(histo_eg_BX_cut1->GetBinContent(4)+histo_eg_BX_cut1->GetBinContent(3));
cout<<endl<<"The total post-firing rate for EG is "<<total_eg_post_rate_cut1*100.<<"%"<<endl;

float total_mu_pre_rate_cut1=(histo_mu_BX_cut1->GetBinContent(2))/(histo_mu_BX_cut1->GetBinContent(2)+histo_mu_BX_cut1->GetBinContent(3));
cout<<endl<<"The total pre-firing rate for MU(g20) is "<<total_mu_pre_rate_cut1*100.<<"%"<<endl;
float total_mu_post_rate_cut1=(histo_mu_BX_cut1->GetBinContent(4))/(histo_mu_BX_cut1->GetBinContent(4)+histo_mu_BX_cut1->GetBinContent(3));
cout<<endl<<"The total post-firing rate for MU(g20) is "<<total_mu_post_rate_cut1*100.<<"%"<<endl;

float total_mu_pre_rate_cut2=(histo_mu_BX_cut2->GetBinContent(2))/(histo_mu_BX_cut2->GetBinContent(2)+histo_mu_BX_cut2->GetBinContent(3));
cout<<endl<<"The total pre-firing rate for MU(8_25) is "<<total_mu_pre_rate_cut2*100.<<"%"<<endl;
float total_mu_post_rate_cut2=(histo_mu_BX_cut2->GetBinContent(4))/(histo_mu_BX_cut2->GetBinContent(4)+histo_mu_BX_cut2->GetBinContent(3));
cout<<"The total post-firing rate for MU(8_25) is "<<total_mu_post_rate_cut2*100.<<"%"<<endl;

float total_jet_pre_rate_cut1=(histo_jet_BX_cut1->GetBinContent(2))/(histo_jet_BX_cut1->GetBinContent(2)+histo_jet_BX_cut1->GetBinContent(3));
cout<<endl<<"The total pre-firing rate for JET is "<<total_jet_pre_rate_cut1*100.<<"%"<<endl;
float total_jet_post_rate_cut1=(histo_jet_BX_cut1->GetBinContent(4))/(histo_jet_BX_cut1->GetBinContent(4)+histo_jet_BX_cut1->GetBinContent(3));
cout<<"The total post-firing rate for JET is "<<total_jet_post_rate_cut1*100.<<"%"<<endl<<endl;

TPaveText *paveCMS = new TPaveText(0.05,0.9,0.93,0.95,"NDC");
	paveCMS->AddText("#bf{CMS #it{Preliminary}}              		                   (13.6 TeV)");
	//paveCMS->AddText("#bf{CMS #it{Preliminary}}                RunF 2017 (13 TeV)");
	//paveCMS->AddText("#bf{CMS #it{Preliminary}}               RunF 2017 + RunD 2018 (13 TeV)");
	paveCMS->SetFillColor(0);
	paveCMS->SetBorderSize(0);
	paveCMS->SetTextSize(0.03);
	paveCMS->SetTextFont(42);

TPaveText *pave_eg_pre_cut1 = new TPaveText(0.6,0.6,0.85,0.85,"NDC");
	pave_eg_pre_cut1->AddText("Electrons pre-firing rate - "+era);
	pave_eg_pre_cut1->AddText("p_{T}^{L1}>15GeV & p_{T}^{L1}<26GeV");
	pave_eg_pre_cut1->AddText("p_{T}^{offl}>12GeV & p_{T}^{offl}<23GeV");
	pave_eg_pre_cut1->AddText(Form("Total rate %1.3f %%",total_eg_pre_rate_cut1*100.));
	pave_eg_pre_cut1->SetFillColor(0);
	pave_eg_pre_cut1->SetBorderSize(0);
	pave_eg_pre_cut1->SetTextSize(0.03);
	pave_eg_pre_cut1->SetTextColor(kRed);
	pave_eg_pre_cut1->SetTextFont(42);

TPaveText *pave_eg_post_cut1 = new TPaveText(0.6,0.6,0.85,0.85,"NDC");
	pave_eg_post_cut1->AddText("Electrons post-firing rate - "+era);
	pave_eg_post_cut1->AddText("p_{T}^{L1}>15GeV & p_{T}^{L1}<26GeV");
	pave_eg_post_cut1->AddText("p_{T}^{offl}>12GeV & p_{T}^{offl}<23GeV");
	pave_eg_post_cut1->AddText(Form("Total rate %1.3f %%",total_eg_post_rate_cut1*100.));
	pave_eg_post_cut1->SetFillColor(0);
	pave_eg_post_cut1->SetBorderSize(0);
	pave_eg_post_cut1->SetTextSize(0.03);
	pave_eg_post_cut1->SetTextColor(kRed);
	pave_eg_post_cut1->SetTextFont(42);

TPaveText *pave_mu_pre_cut1 = new TPaveText(0.6,0.6,0.85,0.85,"NDC");
	pave_mu_pre_cut1->AddText("Muons pre-firing rate - "+era);
	pave_mu_pre_cut1->AddText("p_{T}^{L1}>10 & p_{T}^{L1}<21GeV");
	pave_mu_pre_cut1->AddText("p_{T}^{offl}>8GeV & p_{T}^{offl}<25GeV");
	pave_mu_pre_cut1->AddText(Form("Total rate %1.3f %%",total_mu_pre_rate_cut1*100.));
	pave_mu_pre_cut1->SetFillColor(0);
	pave_mu_pre_cut1->SetBorderSize(0);
	pave_mu_pre_cut1->SetTextSize(0.03);
	pave_mu_pre_cut1->SetTextColor(kRed);
	pave_mu_pre_cut1->SetTextFont(42);

TPaveText *pave_mu_post_cut1 = new TPaveText(0.6,0.6,0.85,0.85,"NDC");
	pave_mu_post_cut1->AddText("Muons post-firing rate - "+era);
	pave_mu_post_cut1->AddText("p_{T}^{L1}>10 & p_{T}^{L1}<21GeV");
	pave_mu_post_cut1->AddText("p_{T}^{offl}>8GeV & p_{T}^{offl}<25GeV");
	pave_mu_post_cut1->AddText(Form("Total rate %1.3f %%",total_mu_post_rate_cut1*100.));
	pave_mu_post_cut1->SetFillColor(0);
	pave_mu_post_cut1->SetBorderSize(0);
	pave_mu_post_cut1->SetTextSize(0.03);
	pave_mu_post_cut1->SetTextColor(kRed);
	pave_mu_post_cut1->SetTextFont(42);

TPaveText *pave_mu_pre_cut2 = new TPaveText(0.6,0.6,0.85,0.85,"NDC");
	pave_mu_pre_cut2->AddText("Muons pre-firing rate - "+era);
	pave_mu_pre_cut2->AddText("p_{T}^{L1}>22GeV");
	pave_mu_pre_cut2->AddText("p_{T}^{offl}>20GeV");
	pave_mu_pre_cut2->AddText(Form("Total rate %1.3f %%",total_mu_pre_rate_cut2*100.));
	pave_mu_pre_cut2->SetFillColor(0);
	pave_mu_pre_cut2->SetBorderSize(0);
	pave_mu_pre_cut2->SetTextSize(0.03);
	pave_mu_pre_cut2->SetTextColor(kRed);
	pave_mu_pre_cut2->SetTextFont(42);

TPaveText *pave_mu_post_cut2 = new TPaveText(0.6,0.6,0.85,0.85,"NDC");
	pave_mu_post_cut2->AddText("Muons post-firing rate - "+era);
	pave_mu_post_cut2->AddText("p_{T}^{L1}>22GeV");
	pave_mu_post_cut2->AddText("p_{T}^{offl}>20GeV");
	pave_mu_post_cut2->AddText(Form("Total rate %1.3f %%",total_mu_post_rate_cut2*100.));
	pave_mu_post_cut2->SetFillColor(0);
	pave_mu_post_cut2->SetBorderSize(0);
	pave_mu_post_cut2->SetTextSize(0.03);
	pave_mu_post_cut2->SetTextColor(kRed);
	pave_mu_post_cut2->SetTextFont(42);
	
TPaveText *pave_jet_pre_cut1 = new TPaveText(0.6,0.6,0.85,0.85,"NDC");
	pave_jet_pre_cut1->AddText("Jets pre-firing rate - "+era);
	pave_jet_pre_cut1->AddText("p_{T}^{L1}>100 & p_{T}^{L1}<150GeV");
	pave_jet_pre_cut1->AddText("p_{T}^{offl}>90GeV & p_{T}^{offl}<160GeV");
	pave_jet_pre_cut1->AddText(Form("Total rate %1.4f %%",total_jet_pre_rate_cut1*100.));
	pave_jet_pre_cut1->SetFillColor(0);
	pave_jet_pre_cut1->SetBorderSize(0);
	pave_jet_pre_cut1->SetTextSize(0.03);
	pave_jet_pre_cut1->SetTextColor(kRed);
	pave_jet_pre_cut1->SetTextFont(42);

TPaveText *pave_jet_post_cut1 = new TPaveText(0.6,0.6,0.85,0.85,"NDC");
	pave_jet_post_cut1->AddText("Jets post-firing rate - "+era);
	pave_jet_post_cut1->AddText("p_{T}^{L1}>100 & p_{T}^{L1}<150GeV");
	pave_jet_post_cut1->AddText("p_{T}^{offl}>90GeV & p_{T}^{offl}<160GeV");
	pave_jet_post_cut1->AddText(Form("Total rate %1.4f %%",total_jet_post_rate_cut1*100.));
	pave_jet_post_cut1->SetFillColor(0);
	pave_jet_post_cut1->SetBorderSize(0);
	pave_jet_post_cut1->SetTextSize(0.03);
	pave_jet_post_cut1->SetTextColor(kRed);
	pave_jet_post_cut1->SetTextFont(42);

TPaveText *pave_eg_cut1 = new TPaveText(0.6,0.6,0.85,0.85,"NDC");
	pave_eg_cut1->AddText("Electrons - "+era);
	pave_eg_cut1->AddText("p_{T}^{L1}>15 & p_{T}^{L1}<26GeV");
	pave_eg_cut1->AddText("p_{T}^{offl}>12GeV & p_{T}^{offl}<23GeV");
	pave_eg_cut1->AddText(Form("Total pre-firing  rate %1.3f %%",total_eg_pre_rate_cut1*100.));
	pave_eg_cut1->AddText(Form("Total post-firing rate %1.3f %%",total_eg_post_rate_cut1*100.));
	pave_eg_cut1->SetFillColor(0);
	pave_eg_cut1->SetBorderSize(0);
	pave_eg_cut1->SetTextSize(0.03);
	pave_eg_cut1->SetTextColor(kRed);
	pave_eg_cut1->SetTextFont(42);

TPaveText *pave_mu_cut1 = new TPaveText(0.6,0.6,0.85,0.85,"NDC");
	pave_mu_cut1->AddText("Muons - "+era);
	pave_mu_cut1->AddText("p_{T}^{L1}>10 & p_{T}^{L1}<21GeV");
	pave_mu_cut1->AddText("p_{T}^{offl}>8GeV & p_{T}^{offl}<25GeV");
	pave_mu_cut1->AddText(Form("Total pre-firing  rate %1.3f %%",total_mu_pre_rate_cut1*100.));
	pave_mu_cut1->AddText(Form("Total post-firing rate %1.3f %%",total_mu_post_rate_cut1*100.));
	pave_mu_cut1->SetFillColor(0);
	pave_mu_cut1->SetBorderSize(0);
	pave_mu_cut1->SetTextSize(0.03);
	pave_mu_cut1->SetTextColor(kRed);
	pave_mu_cut1->SetTextFont(42);

TPaveText *pave_mu_cut2 = new TPaveText(0.6,0.4,0.85,0.65,"NDC");
	pave_mu_cut2->AddText("Muons - "+era);
	pave_mu_cut2->AddText("p_{T}^{L1}>22GeV");
	pave_mu_cut2->AddText("p_{T}^{offl}>20GeV");
	pave_mu_cut2->AddText(Form("Total pre-firing  rate %1.3f %%",total_mu_pre_rate_cut2*100.));
	pave_mu_cut2->AddText(Form("Total post-firing rate %1.3f %%",total_mu_post_rate_cut2*100.));
	pave_mu_cut2->SetFillColor(0);
	pave_mu_cut2->SetBorderSize(0);
	pave_mu_cut2->SetTextSize(0.03);
	pave_mu_cut2->SetTextColor(kRed);
	pave_mu_cut2->SetTextFont(42);
		
TPaveText *pave_jet_cut1 = new TPaveText(0.6,0.6,0.85,0.85,"NDC");
	pave_jet_cut1->AddText("Jets - "+era);
	pave_jet_cut1->AddText("p_{T}^{L1}>100 & p_{T}^{L1}<150GeV");
	pave_jet_cut1->AddText("p_{T}^{offl}>90GeV & p_{T}^{offl}<160GeV");
	pave_jet_cut1->AddText(Form("Total pre-firing  rate %1.4f %%",total_jet_pre_rate_cut1*100.));
	pave_jet_cut1->AddText(Form("Total post-firing rate %1.4f %%",total_jet_post_rate_cut1*100.));
	pave_jet_cut1->SetFillColor(0);
	pave_jet_cut1->SetBorderSize(0);
	pave_jet_cut1->SetTextSize(0.03);
	pave_jet_cut1->SetTextColor(kRed);
	pave_jet_cut1->SetTextFont(42);

/// BX histos
TCanvas *c1=new TCanvas("c1","",800,600);
c1->cd();
c1->SetLogy();
histo_eg_BX_cut1->GetXaxis()->SetTitleOffset(1.2); 
histo_eg_BX_cut1->SetFillColor(0);
histo_eg_BX_cut1->SetLineWidth(2);
histo_eg_BX_cut1->SetLineColor(kBlue);
histo_eg_BX_cut1->SetMarkerSize(0.1);
histo_eg_BX_cut1->GetXaxis()->SetTitle("BX");
histo_eg_BX_cut1->GetYaxis()->SetTitle("Entries");
histo_eg_BX_cut1->Draw();
paveCMS->Draw("Same");
pave_eg_cut1->Draw("same");
c1->Print("../plots/"+era+"/eg_bx.png");

TCanvas *c2=new TCanvas("c2","",800,600);
c2->cd();
c2->SetLogy();
histo_mu_BX_cut1->GetXaxis()->SetTitleOffset(1.2); 
histo_mu_BX_cut1->SetFillColor(0);
histo_mu_BX_cut1->SetLineWidth(2);
histo_mu_BX_cut1->SetLineColor(kBlue);
histo_mu_BX_cut1->SetMarkerSize(0.1);
histo_mu_BX_cut1->GetXaxis()->SetTitle("BX");
histo_mu_BX_cut1->GetYaxis()->SetTitle("Entries");
histo_mu_BX_cut1->Draw();
paveCMS->Draw("Same");
pave_mu_cut1->Draw("same");
c2->Print("../plots/"+era+"/mu_bx_8_25.png");

TCanvas *c3=new TCanvas("c3","",800,600);
c3->cd();
c3->SetLogy();
histo_mu_BX_cut2->GetXaxis()->SetTitleOffset(1.2); 
histo_mu_BX_cut2->SetFillColor(0);
histo_mu_BX_cut2->SetLineWidth(2);
histo_mu_BX_cut2->SetLineColor(kBlue);
histo_mu_BX_cut2->SetMarkerSize(0.1);
histo_mu_BX_cut2->GetXaxis()->SetTitle("BX");
histo_mu_BX_cut2->GetYaxis()->SetTitle("Entries");
histo_mu_BX_cut2->Draw();
paveCMS->Draw("Same");
pave_mu_cut2->Draw("same");
c3->Print("../plots/"+era+"/mu_bx_g20.png");

TCanvas *c4=new TCanvas("c4","",800,600);
c4->cd();
c4->SetLogy();
histo_jet_BX_cut1->GetXaxis()->SetTitleOffset(1.2); 
histo_jet_BX_cut1->SetFillColor(0);
histo_jet_BX_cut1->SetLineWidth(2);
histo_jet_BX_cut1->SetLineColor(kBlue);
histo_jet_BX_cut1->SetMarkerSize(0.1);
histo_jet_BX_cut1->GetXaxis()->SetTitle("BX");
histo_jet_BX_cut1->GetYaxis()->SetTitle("Entries");
histo_jet_BX_cut1->Draw();
paveCMS->Draw("Same");
pave_jet_cut1->Draw("same");
c4->Print("../plots/"+era+"/jet_bx.png");


// Rates histos
TCanvas *c5=new TCanvas("c5","",800,600);
c5->cd();
rate_vs_eta_eg_cut1[0]->SetFillColor(0);
rate_vs_eta_eg_cut1[0]->SetLineWidth(2);
rate_vs_eta_eg_cut1[0]->SetLineColor(kBlue);
rate_vs_eta_eg_cut1[0]->GetYaxis()->SetRangeUser(0.,.21);
rate_vs_eta_eg_cut1[0]->SetMarkerSize(0.1);
rate_vs_eta_eg_cut1[0]->GetXaxis()->SetTitle("#eta_{offl}");
rate_vs_eta_eg_cut1[0]->GetYaxis()->SetTitle("Rate");
rate_vs_eta_eg_cut1[0]->Draw("ep");
paveCMS->Draw("Same");
pave_eg_pre_cut1->Draw("same");
c5->Print("../plots/"+era+"/eg_pre_rate_eta.png");

TCanvas *c6=new TCanvas("c6","",800,600);
c6->cd();
rate_vs_eta_eg_cut1[1]->SetFillColor(0);
rate_vs_eta_eg_cut1[1]->SetLineWidth(2);
rate_vs_eta_eg_cut1[1]->SetLineColor(kBlue);
rate_vs_eta_eg_cut1[1]->GetYaxis()->SetRangeUser(0.,.21);
rate_vs_eta_eg_cut1[1]->SetMarkerSize(0.1);
rate_vs_eta_eg_cut1[1]->GetXaxis()->SetTitle("#eta_{offl}");
rate_vs_eta_eg_cut1[1]->GetYaxis()->SetTitle("Rate");
rate_vs_eta_eg_cut1[1]->Draw("ep");
paveCMS->Draw("Same");
pave_eg_post_cut1->Draw("same");
c6->Print("../plots/"+era+"/eg_post_rate_eta.png");

TCanvas *c7=new TCanvas("c7","",800,600);
c7->cd();
rate_vs_eta_mu_cut1[0]->SetFillColor(0);
rate_vs_eta_mu_cut1[0]->SetLineWidth(2);
rate_vs_eta_mu_cut1[0]->SetLineColor(kBlue);
rate_vs_eta_mu_cut1[0]->GetYaxis()->SetRangeUser(0.,1.01);
rate_vs_eta_mu_cut1[0]->SetMarkerSize(0.1);
rate_vs_eta_mu_cut1[0]->GetXaxis()->SetTitle("#eta_{offl}");
rate_vs_eta_mu_cut1[0]->GetYaxis()->SetTitle("Rate");
rate_vs_eta_mu_cut1[0]->Draw("ep");
paveCMS->Draw("Same");
pave_mu_pre_cut1->Draw("same");
c7->Print("../plots/"+era+"/mu_8_25_pre_rate_eta.png");

TCanvas *c8=new TCanvas("c8","",800,600);
c8->cd();
rate_vs_eta_mu_cut1[1]->SetFillColor(0);
rate_vs_eta_mu_cut1[1]->SetLineWidth(2);
rate_vs_eta_mu_cut1[1]->SetLineColor(kBlue);
rate_vs_eta_mu_cut1[1]->GetYaxis()->SetRangeUser(0.,1.01);
rate_vs_eta_mu_cut1[1]->SetMarkerSize(0.1);
rate_vs_eta_mu_cut1[1]->GetXaxis()->SetTitle("#eta_{offl}");
rate_vs_eta_mu_cut1[1]->GetYaxis()->SetTitle("Rate");
rate_vs_eta_mu_cut1[1]->Draw("ep");
paveCMS->Draw("Same");
pave_mu_post_cut1->Draw("same");
c8->Print("../plots/"+era+"/mu_8_25_post_rate_eta.png");

TCanvas *c9=new TCanvas("c9","",800,600);
c9->cd();
rate_vs_eta_mu_cut2[0]->SetFillColor(0);
rate_vs_eta_mu_cut2[0]->SetLineWidth(2);
rate_vs_eta_mu_cut2[0]->SetLineColor(kBlue);
rate_vs_eta_mu_cut2[0]->GetYaxis()->SetRangeUser(0.,1.01);
rate_vs_eta_mu_cut2[0]->SetMarkerSize(0.1);
rate_vs_eta_mu_cut2[0]->GetXaxis()->SetTitle("#eta_{offl}");
rate_vs_eta_mu_cut2[0]->GetYaxis()->SetTitle("Rate");
rate_vs_eta_mu_cut2[0]->Draw("ep");
paveCMS->Draw("Same");
pave_mu_pre_cut2->Draw("same");
c9->Print("../plots/"+era+"/mu_g20_pre_rate_eta.png");

TCanvas *c10=new TCanvas("c10","",800,600);
c10->cd();
rate_vs_eta_mu_cut2[1]->SetFillColor(0);
rate_vs_eta_mu_cut2[1]->SetLineWidth(2);
rate_vs_eta_mu_cut2[1]->SetLineColor(kBlue);
rate_vs_eta_mu_cut2[1]->GetYaxis()->SetRangeUser(0.,1.01);
rate_vs_eta_mu_cut2[1]->SetMarkerSize(0.1);
rate_vs_eta_mu_cut2[1]->GetXaxis()->SetTitle("#eta_{offl}");
rate_vs_eta_mu_cut2[1]->GetYaxis()->SetTitle("Rate");
rate_vs_eta_mu_cut2[1]->Draw("ep");
paveCMS->Draw("Same");
pave_mu_post_cut2->Draw("same");
c10->Print("../plots/"+era+"/mu_g20_post_rate_eta.png");

////
TCanvas *c11=new TCanvas("c11","",800,600);
c11->cd();
rate_vs_eta_jet_cut1[0]->SetFillColor(0);
rate_vs_eta_jet_cut1[0]->SetLineWidth(2);
rate_vs_eta_jet_cut1[0]->SetLineColor(kBlue);
rate_vs_eta_jet_cut1[0]->GetYaxis()->SetRangeUser(0.,.21);
rate_vs_eta_jet_cut1[0]->SetMarkerSize(0.1);
rate_vs_eta_jet_cut1[0]->GetXaxis()->SetTitle("#eta_{offl}");
rate_vs_eta_jet_cut1[0]->GetYaxis()->SetTitle("Rate");
rate_vs_eta_jet_cut1[0]->Draw("ep");
paveCMS->Draw("Same");
pave_jet_pre_cut1->Draw("same");
c11->Print("../plots/"+era+"/jet_pre_rate_eta.png");

TCanvas *c12=new TCanvas("c12","",800,600);
c12->cd();
rate_vs_eta_jet_cut1[1]->SetFillColor(0);
rate_vs_eta_jet_cut1[1]->SetLineWidth(2);
rate_vs_eta_jet_cut1[1]->SetLineColor(kBlue);
rate_vs_eta_jet_cut1[1]->GetYaxis()->SetRangeUser(0.,.21);
rate_vs_eta_jet_cut1[1]->SetMarkerSize(0.1);
rate_vs_eta_jet_cut1[1]->GetXaxis()->SetTitle("#eta_{offl}");
rate_vs_eta_jet_cut1[1]->GetYaxis()->SetTitle("Rate");
rate_vs_eta_jet_cut1[1]->Draw("ep");
paveCMS->Draw("Same");
pave_jet_post_cut1->Draw("same");
c12->Print("../plots/"+era+"/jet_post_rate_eta.png");

TCanvas *c13=new TCanvas("c13","",600,600);
c13->cd();
c13->SetRightMargin(0.17);
map_eta_phi_eg_cut1[0]->DrawNormalized("colz");
paveCMS->Draw("Same");
c13->Print("../plots/"+era+"/eg_pre_map_eta_phi.png");

TCanvas *c14=new TCanvas("c14","",600,600);
c14->cd();
c14->SetRightMargin(0.17);
map_eta_phi_eg_cut1[1]->DrawNormalized("colz");
paveCMS->Draw("Same");
c14->Print("../plots/"+era+"/eg_post_map_eta_phi.png");

TCanvas *c15=new TCanvas("c15","",600,600);
c15->cd();
c15->SetRightMargin(0.17);
map_eta_phi_mu_cut1[0]->DrawNormalized("colz");
paveCMS->Draw("Same");
c15->Print("../plots/"+era+"/mu_8_25_pre_map_eta_phi.png");

TCanvas *c16=new TCanvas("c16","",600,600);
c16->cd();
c16->SetRightMargin(0.17);
map_eta_phi_mu_cut1[1]->DrawNormalized("colz");
paveCMS->Draw("Same");
c16->Print("../plots/"+era+"/mu_8_25_post_map_eta_phi.png");

TCanvas *c17=new TCanvas("c17","",600,600);
c17->cd();
c17->SetRightMargin(0.17);
map_eta_phi_mu_cut2[0]->DrawNormalized("colz");
paveCMS->Draw("Same");
c17->Print("../plots/"+era+"/mu_g20_pre_map_eta_phi.png");

TCanvas *c18=new TCanvas("c18","",600,600);
c18->cd();
c18->SetRightMargin(0.17);
map_eta_phi_mu_cut2[1]->DrawNormalized("colz");
paveCMS->Draw("Same");
c18->Print("../plots/"+era+"/mu_g20_post_map_eta_phi.png");


TCanvas *c19=new TCanvas("c19","",600,600);
c19->cd();
c19->SetRightMargin(0.17);
map_eta_phi_jet_cut1[0]->DrawNormalized("colz");
paveCMS->Draw("Same");
c19->Print("../plots/"+era+"/jet_pre_map_eta_phi.png");

TCanvas *c20=new TCanvas("c20","",600,600);
c20->cd();
c20->SetRightMargin(0.17);
map_eta_phi_jet_cut1[1]->DrawNormalized("colz");
paveCMS->Draw("Same");
c20->Print("../plots/"+era+"/jet_post_map_eta_phi.png");
}

////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
///////////////  end of code ///////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
/*
-> objects cuts !
-----------------------------------
cut1_EGs:	l1tPt in (15,26)
		offPt in (12,23)
-----------------------------------
cut1_Jets:	l1tPt in (100,150)
		offPt in (90,160)
-----------------------------------		
cut1_Mus:	l1tPt in (10,21)
		offPt in (8,25)
-----------------------------------
cut2_Mus:	l1tPt in (22,inf)
		offPt in (20,inf)
		
-> Names of histos:
histo_eg_eta_cut1->
histo_mu_eta_cut1->
histo_mu_eta_cut2->
histo_jet_eta_cut1->
rate_vs_eta_eg_cut1->
rate_vs_eta_eg_cut1_num->
rate_vs_eta_eg_cut1_den->
rate_vs_eta_mu_cut1->
rate_vs_eta_mu_cut1_num->
rate_vs_eta_mu_cut1_den->
rate_vs_eta_mu_cut2->
rate_vs_eta_mu_cut2_num->
rate_vs_eta_mu_cut2_den->
rate_vs_eta_jet_cut1->
rate_vs_eta_jet_cut1_num->
rate_vs_eta_jet_cut1_den->

*/
