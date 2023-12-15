// Classe pour représenter une case de taxe
class CaseTaxe : public Case {
protected:
    int montant;

public:
    CaseTaxe(int _montant) : montant(_montant) {}

    void action() const override {
        std::cout << "Vous êtes sur une case de taxe. Vous devez payer " << montant << " médailles olympiques." << std::endl;
    }
};

