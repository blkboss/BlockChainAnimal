#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <functional> // Pour std::hash
#include <ctime>

class Block 
{
public:
    std::string previousHash;
    std::string data;
    std::time_t timestamp;
    size_t hash;

    Block(std::string data, std::string previousHash)
        : data(data), previousHash(previousHash), timestamp(std::time(nullptr)) {
        hash = calculateHash();
    }

    size_t calculateHash() 
    {
        std::stringstream ss;
        ss << previousHash << timestamp << data;
        std::string input = ss.str();

        std::hash<std::string> hasher;
        return hasher(input);
    }
};

class Blockchain 
{
public:
    std::vector<Block> chain;

    Blockchain() 
    {
        chain.emplace_back("Genesis Block", "0");
    }

    void addBlock(std::string data) 
    {
        std::string previousHash = std::to_string(chain.back().hash);
        chain.emplace_back(data, previousHash);
    }

    void displayChain() 
    {
        for (const auto& block : chain) 
        {
            std::cout << "Block Hash: " << block.hash << std::endl;
            std::cout << "Previous Hash: " << block.previousHash << std::endl;
            std::cout << "Data: " << block.data << std::endl;
            //std::cout << "Timestamp: " << std::ctime(&block.timestamp);
            std::cout << "-------------------------------" << std::endl;
        }
    }
};

class Animal 
{
protected:
    int age;
    int poids;
    std::string communaute;

public:
    Animal(int __age, int __poids, std::string __communaute) : age(__age), poids(__poids), communaute(__communaute) {}

    ~Animal() {}

    void manger() 
    {
        std::cout << "J'aime manger et j'ai : " << age << " ans" << " \n " << std::endl;
    }

    void mourir() 
    {
        std::cout << "A DIEU LES GARS. Mes " << poids << " kilos me tuent à petit feu." << " \n " << std::endl;
        std::cout << "Je suis de la communauté des " << communaute << std::endl;
    }
};

class Mouton : public Animal 
{
protected:
    std::string qualiteLaine;

public:
    Mouton(int __age, int __poids, std::string __communaute, std::string __qualiteLaine)
        : Animal(__age, __poids, __communaute), qualiteLaine(__qualiteLaine) {}

    ~Mouton() {}

    void beler() 
    {
        std::cout << "beeeee beeeee !!!!!" << std::endl;
    }
};

class Chien : public Animal 
{
protected:
    std::string poils;

public:
    Chien(int __age, int __poids, std::string __communaute, std::string __poils)
        : Animal(__age, __poids, __communaute), poils(__poils) {}

    ~Chien() {}

    void aboyer() 
    {
        std::cout << "Wouaf Wouaf. J'ai " << age << " ans et " << poids << " kilos. Je suis un chien de race " << communaute << " ayant des poils " << poils << std::endl;
    }
};

Blockchain blockchain; // Déclaration de la blockchain globale

void creer_un_animal() 
{
    int age;
    int poids;
    std::string communaute;
    std::cout << "Quel est l'age de votre animal ??" << std::endl;
    std::cin >> age;
    std::cout << "Quel est le poids de votre animal ??" << std::endl;
    std::cin >> poids;
    std::cout << "De quelle communaute est votre animal ??" << std::endl;
    std::cin >> communaute;
    std::cout << " \n " << std::endl;
    Animal monAnimal(age, poids, communaute);
    monAnimal.manger();
    monAnimal.mourir();

    // Ajouter à la blockchain
    blockchain.addBlock("Animal: " + std::to_string(age) + " ans, " + std::to_string(poids) + " kg, communauté: " + communaute);
}

void creer_un_chien() 
{
    int age;
    int poids;
    std::string communaute;
    std::string poils;
    std::cout << "Quel est l'age de votre chien ??" << std::endl;
    std::cin >> age;
    std::cout << "Quel est le poids de votre chien ??" << std::endl;
    std::cin >> poids;
    std::cout << "De quelle communaute est votre chien ??" << std::endl;
    std::cin.ignore(); // Pour ignorer le '\n' restant dans le buffer
    std::getline(std::cin, communaute);
    std::cout << "Comment sont les poils de votre chien ??" << std::endl;
    std::getline(std::cin, poils);
    std::cout << " \n " << std::endl;
    Chien monChien(age, poids, communaute, poils);
    monChien.aboyer();

    // Ajouter à la blockchain
    blockchain.addBlock("Chien: " + std::to_string(age) + " ans, " + std::to_string(poids) + " kg, communauté: " + communaute + ", poils: " + poils);
}

int main() 
{
    creer_un_animal();
    std::cout << " \n " << std::endl;
    creer_un_chien();

    // Afficher la blockchain
    blockchain.displayChain();

    return 0;
}
