// Classe pour représenter une case de travaux en pause
class CaseTravauxEnPause : public Case {
public:
    void action() const override {
        std::cout << "Vous êtes sur la case Travaux en pause (équivalent à la visite simple)." << std::endl;
    }
};

