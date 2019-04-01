#ifndef __MLBSOUVENIR_H_INCL__
#define __MLBSOUVENIR_H_INCL__

/**
 * TODO: Add class description
 * 
 * @author   edt
 */
class MLBSouvenir
{
public:
    // Constructor
    MLBSouvenir();

    // Destructor
    virtual ~MLBSouvenir();

    // Copy constructor
    // TODO: Uncomment the copy constructor when you need it.
    //MLBSouvenir(const MLBSouvenir& src);

    // Assignment operator
    // TODO: Uncomment the assignment operator when you need it.
    //MLBSouvenir& operator=(const MLBSouvenir& src);
private:
    static  int NextNumber;
    int     m_nNumber;
    string  m_sName;
    float   m_fPrice;
    bool    m_bInitialized;
    bool    m_bDeleted;
    float   m_TotalPurchased;
};

// Constructor implementation
inline MLBSouvenir::MLBSouvenir()
{
}

// Destructor implementation
inline MLBSouvenir::~MLBSouvenir()
{
}

// TODO: Uncomment the copy constructor when you need it.
//inline MLBSouvenir::MLBSouvenir(const MLBSouvenir& src)
//{
//   // TODO: copy
//}

// TODO: Uncomment the assignment operator when you need it.
//inline MLBSouvenir& MLBSouvenir::operator=(const MLBSouvenir& rhs)
//{
//   if (this == &rhs) {
//      return *this;
//   }
//
//   // TODO: assignment
//
//   return *this;
//}

#endif // __MLBSOUVENIR_H_INCL__
