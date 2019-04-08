#ifndef __MLBUSER_H_INCL__
#define __MLBUSER_H_INCL__

/**
 * TODO: Add class description
 * 
 * @author   edt
 */
class MLBUser
{
public:
    // Constructor
    MLBUser();

    // Destructor
    virtual ~MLBUser();

    // Copy constructor
    // TODO: Uncomment the copy constructor when you need it.
    //MLBUser(const MLBUser& src);

    // Assignment operator
    // TODO: Uncomment the assignment operator when you need it.
    //MLBUser& operator=(const MLBUser& src);
private:
    static  int NextNumber;
    int     m_nNumber;
    string  m_sName;
    bool    m_bInitialized;
    bool    m_bDeleted;
    bool    m_bAdministrator;
    bool    m_Blocked;
};

// Constructor implementation
inline MLBUser::MLBUser()
{
}

// Destructor implementation
inline MLBUser::~MLBUser()
{
}

// TODO: Uncomment the copy constructor when you need it.
//inline MLBUser::MLBUser(const MLBUser& src)
//{
//   // TODO: copy
//}

// TODO: Uncomment the assignment operator when you need it.
//inline MLBUser& MLBUser::operator=(const MLBUser& rhs)
//{
//   if (this == &rhs) {
//      return *this;
//   }
//
//   // TODO: assignment
//
//   return *this;
//}

#endif // __MLBUSER_H_INCL__
