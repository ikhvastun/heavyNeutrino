#ifndef GenMatching_h
#define GenMatching_h

//include other parts of framework
#include "heavyNeutrino/multilep/plugins/multilep.h"
#include "heavyNeutrino/multilep/interface/GenTools.h"


class multilep;

class GenMatching{
  public:
    GenMatching(const edm::ParameterSet& iConfig, multilep*);
    ~GenMatching(){};

    //check if given reco candidate is prompt
    bool isPrompt(const reco::Candidate&, const reco::GenParticle&) const;
    void setGenParticles(const edm::Event&);    

    //fill match variables
    template <typename Lepton> void fillMatchingVars(const Lepton& reco){
        const reco::GenParticle* match = findGenMatch(reco);
        if(match != nullptr){
            matchIsPrompt = isPrompt(reco, *match);
            matchPdgId = match->pdgId();
            provenance = GenTools::provenance(*match, *genParticles);
            provenanceCompressed = (matchIsPrompt ? 0 : GenTools::provenanceCompressed(*match, *genParticles) );
            provenanceConversion = GenTools::provenanceConversion(*match, *genParticles);
        } else{
            matchIsPrompt = false;
            matchPdgId = 0;
            provenanceCompressed = 4;
            provenance = 18;
            provenanceConversion = 99;
        }
    }

    //return values
    int pdgIdMatch() const {return matchPdgId; }
    bool promptMatch() const {return matchIsPrompt;}
    unsigned getProvenance() const {return provenance;}
    unsigned getProvenanceCompressed() const{ return provenanceCompressed; }
    unsigned getProvenanceConversion() const{ return provenanceConversion; }

  private:
    multilep* multilepAnalyzer;
    edm::Handle<std::vector<reco::GenParticle>> genParticles;
    const reco::GenParticle* geometricMatch(const reco::Candidate&, const bool differentId = false) const;

    template<typename Lepton> const reco::GenParticle* findGenMatch(const Lepton& lepton) const{
        const reco::GenParticle* match = lepton.genParticle();
        //short circuit assumed here!
        if(match == nullptr || match->pdgId() != lepton.pdgId()){
            return geometricMatch(lepton);
        }
        return match;
    }

    bool considerForMatching(const reco::Candidate&, const reco::GenParticle&, const bool differentId = false) const;
    bool sameParticle(const reco::Candidate&, const reco::GenParticle&) const;
    int matchPdgId;
    bool matchIsPrompt;
    unsigned provenance;
    unsigned provenanceCompressed;
    unsigned provenanceConversion;
};
#endif
