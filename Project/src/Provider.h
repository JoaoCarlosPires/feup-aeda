#ifndef PROVIDER_H
#define PROVIDER_H

#include <string>
#include <queue>
#include <vector>

/// \brief Struct for a Provider's Equipment.
struct Equipment {
    int football_kit; ///< Football Kit.
    int balls; ///< Balls.
    int football_boots; ///< Football Boots.
    int cones; ///< Cones.
    int goal; ///< Goal.
    int tactics_board; ///< Tactics Board.
    int medical_kit; ///< Medical Kit.
    int water_bottles; ///< Water Bottles.
};

/// \brief Class for a Provider.
class Provider {
private:
    std::string name; ///< Name.
    double reputation; ///< Reputation.
    Equipment equipment; ///< Equipment.

public:
    /// \brief Default Empty-Constructor.
    Provider() {}
    /// \brief Constructor to initialize a Provider.
    /// \param name Name of the Provider
    /// \param reputation Reputation of the Provider
    /// \param equipment Struct of type Equipment
    Provider(std::string name, double reputation, Equipment equipment);
    
    /// \brief Function to show the information of a Provider.
    void showInfo() const;

    /// \brief Function to show the Name, Reputation and Item of a Provider.
    /// \param item Item to show
    void showItem(int item) const;

    /// \brief Function to get the name of a Provider.
    /// \return shows the name of a Provider
    std::string getName() const;

    /// \brief Function to set the name of a Provider.
    /// \param n Name of the Provider
    void setName(std::string n);
    
    /// \brief Function to get the reputation of a Provider.
    /// \return shows the reputation of a Provider
    double getReputation() const;

    /// \brief Function to set the reputation of a Provider.
    /// \param rate Reputation of the Provider
    void setReputation(double rate);

    /// \brief Function to get the equipment of a Provider.
    /// \return shows the equipment of a Provider
    Equipment getEquipment() const;

    /// \brief Function to set the equipment of a Provider.
    /// \param nballs Number of Balls of the Provider
    /// \param ncones Number of Cones of the Provider
    /// \param nfootball_boots Number of Football Boots of the Provider
    /// \param nfootball_kit Number of Football Kits of the Provider
    /// \param ngoal Number of Goals of the Provider
    /// \param nmedical_kit Numbers of Medical Kits of the Provider
    /// \param ntactics_board Number of Tactics Boards of the Provider
    /// \param nwater_bottles Number of Water Bottles of the Provider
    void setEquipment(int nfootball_kit, int nballs, int nfootball_boots, int ncones, int ngoal, int ntactics_board, int nmedical_kit, int nwater_bottles);

    /// \brief Function to set the new value of an item of equipment of a Provider.
    /// \param item Item whose quantity is to be changed
    /// \param new_value New value of the item quantity
    void setEquipment2(int item, int new_value);

    /// \brief Overload of < operator comparing them by reputation
    /// \param p Provider ot compare the object with
    /// \return true if object's reputation is lower than p's reputation
    bool operator < (const Provider &p) const;

    /// \brief Overload of == operator comparing them by reputation
    /// \param p Provider ot compare the object with
    /// \return true if objects' reputation is the same, false otherwise
    bool operator == (const Provider &p) const;

    /// \brief Overload of != operator comparing them by reputation
    /// \param p Provider ot compare the object with
    /// \return true if objects' reputation is different, false if equal
    bool operator != (const Provider &p) const;
};

/// \brief Class for a Provider Priority Queue.
class ProviderPriorityQueue {

private:

    std::priority_queue<Provider> provider; ///< Provider.

public:

    /// \brief Default empty-constructor.
    ProviderPriorityQueue() {};
    
    /// \brief Function to add a Provider.
    /// \param p Provider
    void addProvider(Provider &p);

    /// \brief Function to remove a Provider.
    /// \param p Provider
    void removeProvider(Provider p);

    /// \brief Function to get the providers
    /// \return returns a priority queue with all the providers
    std::priority_queue<Provider > getProviders();

    /// \brief Function to search a Provider by name.
    /// \param name Provider's name
    /// \return shows the Providers with that name
    std::vector<Provider> searchName(std::string name);

    /// \brief Function to search a Provider by reputation.
    /// \param rep Provider's reputation
    /// \return shows the Providers with a reputation equal or higher than rep
    std::vector<Provider> searchReputation(double rep);
    
    /// \brief Function to search a Provider by equipment item.
    /// \param item Provider's Equipment Item
    /// \return shows the Providers with that item in equipment
    std::vector<Provider> searchEquipment(int item);

    /// \brief Function to update the name of a Provider.
    /// \param p Provider
    /// \param name Name of the Provider
    void updateName(Provider p, std::string name);
    
    /// \brief Function to update the reputation of a Provider.
    /// \param p Provider
    /// \param rep Reputation of the Provider
    void updateReputation(Provider p, double rep);

    /// \brief Function to update the value of an item of a Provider.
    /// \param p Provider
    /// \param item Item of the Provider
    /// \param new_value New Value to the Item of the Provider
    void updateEquipmentItem(Provider p, int item, int new_value);

    /// \brief Function to update the equipment of a Provider.
    /// \param p Provider
    /// \param new_equip Equipment of the Provider
    void updateEquipmentAll(Provider p, Equipment new_equip);
    
    /// \brief Function to print the information of all Providers.
    void print() const;

};

#endif


