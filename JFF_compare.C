#include "TFile.h"
#include "TH1.h"
#include "TLatex.h"

void JFF_compare()
{
    TFile *infile = TFile::Open("output/JFF_hists.root");
    TFile *infile_tagged = TFile::Open("output/tagged/JFF_hists.root");

    TH1D *hpt_norm = (TH1D*)infile->Get("hpt_norm");
    TH1D *hz_ptlow = (TH1D*)infile->Get("hz_ptlow");
    TH1D *hz_ptmed = (TH1D*)infile->Get("hz_ptmed");
    TH1D *hz_pthigh = (TH1D*)infile->Get("hz_pthigh");

    TH1D *hpt_norm_tagged = (TH1D*)infile_tagged->Get("hpt_norm");
    TH1D *hz_ptlow_tagged = (TH1D*)infile_tagged->Get("hz_ptlow");
    TH1D *hz_ptmed_tagged = (TH1D*)infile_tagged->Get("hz_ptmed");
    TH1D *hz_pthigh_tagged = (TH1D*)infile_tagged->Get("hz_pthigh");

    TCanvas *c0 = new TCanvas("c0");
    c0->SetLogx();
    c0->SetLogy();

    hz_ptlow->Scale(1./hpt_norm->GetBinContent(1));
    hz_ptlow->GetYaxis()->SetTitle("#frac{1}{#it{N}_{jets}}#frac{d#it{N}}{d#it{z}}");
    hz_ptlow->SetMarkerStyle(8);
    hz_ptlow->SetLineColor(kBlack);
    hz_ptlow->SetMarkerColor(kBlack);

    hz_ptlow_tagged->Scale(1./hpt_norm_tagged->GetBinContent(1));
    hz_ptlow_tagged->SetMarkerStyle(4);
    hz_ptlow_tagged->SetLineColor(kBlack);
    hz_ptlow_tagged->SetMarkerColor(kBlack);

    hz_ptmed->Scale(1./hpt_norm->GetBinContent(2));
    hz_ptmed->SetMarkerStyle(21);
    hz_ptmed->SetLineColor(kBlue);
    hz_ptmed->SetMarkerColor(kBlue);

    hz_ptmed_tagged->Scale(1./hpt_norm_tagged->GetBinContent(2));
    hz_ptmed_tagged->SetMarkerStyle(25);
    hz_ptmed_tagged->SetLineColor(kBlue);
    hz_ptmed_tagged->SetMarkerColor(kBlue);
    
    hz_pthigh->Scale(1./hpt_norm->GetBinContent(3));
    hz_pthigh->SetMarkerStyle(33);
    hz_pthigh->SetLineColor(kRed);
    hz_pthigh->SetMarkerColor(kRed);

    hz_pthigh_tagged->Scale(1./hpt_norm_tagged->GetBinContent(3));
    hz_pthigh_tagged->SetMarkerStyle(27);
    hz_pthigh_tagged->SetLineColor(kRed);
    hz_pthigh_tagged->SetMarkerColor(kRed);

    TLegend *legend = new TLegend(0.3,0.15,0.7,0.55);
    legend->SetTextSize(0.03);
    legend->SetBorderSize(0);

    legend->AddEntry(hz_ptlow, "20 < #it{p_{T,jet}} < 30 GeV/c","pe");
    legend->AddEntry(hz_ptlow_tagged, "20 < #it{p_{T,jet}} < 30 GeV/c (SV tagged)","pe");
    legend->AddEntry(hz_ptmed, "30 < #it{p_{T,jet}} < 50 GeV/c","pe");
    legend->AddEntry(hz_ptmed_tagged, "30 < #it{p_{T,jet}} < 50 GeV/c (SV tagged)","pe"); 
    legend->AddEntry(hz_pthigh, "50 < #it{p_{T,jet}} < 100 GeV/c","pe");
    legend->AddEntry(hz_pthigh_tagged, "50 < #it{p_{T,jet}} < 100 GeV/c (SV tagged)","pe");   


    hz_ptlow->SetMinimum(0.0001);
    hz_ptlow->Draw("E1");
    hz_ptlow_tagged->Draw("E1,same");
    hz_ptmed->Draw("E1,same");
    hz_ptmed_tagged->Draw("E1,same");
    hz_pthigh->Draw("E1,same");
    hz_pthigh_tagged->Draw("E1,same");
    legend->Draw();

    TLatex *latex = new TLatex();    
    latex->SetNDC();
    latex->SetTextSize(0.04);
    latex->SetTextFont(22); 
    latex->DrawLatex(0.4, 0.58, "LHCb Open Data");

    c0->SaveAs("output/compare/hz_tagged_compare.pdf");

}