//Helper class for facilitating the computation of the lepton MVA.
#ifndef Lepton_Mva_Helper
#define Lepton_Mva_Helper

#include "TMVA/Reader.h"
#include <memory>
class LeptonMvaHelper{
    public:
        LeptonMvaHelper();
        double leptonMvaMuon(double pt, double eta, double selectedTrackMult, double miniIsoCharged, double miniIsoNeutral, double ptRel, double ptRatio, double closestJetCsv, double sip3d, double dxy, double dz, double segComp);
        double leptonMvaElectron(double pt, double eta, double selectedTrackMult, double miniIsoCharged, double miniIsoNeutral, double ptRel, double ptRatio, double closestJetCsv, double sip3d, double dxy, double dz, double eleMva);
    private:
        std::shared_ptr<TMVA::Reader> reader[2]; //First entry is for muons, second one for electrons 
        float LepGood_pt,                       //Variables used in MVA computation
        LepGood_eta,
        LepGood_jetNDauChargedMVASel,
        LepGood_miniRelIsoCharged,
        LepGood_miniRelIsoNeutral,
        LepGood_jetPtRelv2,
        LepGood_jetPtRatio,
        LepGood_jetBTagCSV,
        LepGood_sip3d,
        LepGood_dxy,
        LepGood_dz,
        LepGood_segmentCompatibility,
        LepGood_mvaIdSpring16GP;
        void bookCommonVars(double pt, double eta, double selectedTrackMult, double miniIsoCharged, double miniIsoNeutral, double ptRel, double ptRatio, double closestJetCsv, double sip3d, double dxy, double dz); 
};
#endif
