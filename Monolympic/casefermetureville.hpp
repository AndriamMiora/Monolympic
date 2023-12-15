
// Classe pour représenter une case de fermeture de la ville
class CaseFermetureVille : public Case {
public:
    void action() const override {
        std::cout << "Vous êtes sur la case Fermeture de la ville (équivalent à la case prison)." << std::endl;
    }
};

