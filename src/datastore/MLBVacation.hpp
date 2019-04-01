#ifndef __MLBVACATION_H_INCL__
#define __MLBVACATION_H_INCL__

/**
 * TODO: Add class description
 * 
 * @author   edt
 */
class MLBVacation
{
public:
    // Constructor
    MLBVacation();

    // Destructor
    virtual ~MLBVacation();

    // Copy constructor
    // TODO: Uncomment the copy constructor when you need it.
    //MLBVacation(const MLBVacation& src);

    // Assignment operator
    // TODO: Uncomment the assignment operator when you need it.
    //MLBVacation& operator=(const MLBVacation& src);
private:
    static  int NextNumber;
    int     m_nNumber;
    string  m_sName;
    bool    m_bInitialized;
    bool    m_bDeleted;
;

// Constructor implementation
inline MLBVacation::MLBVacation()
{
}

// Destructor implementation
inline MLBVacation::~MLBVacation()
{
}

// TODO: Uncomment the copy constructor when you need it.
//inline MLBVacation::MLBVacation(const MLBVacation& src)
//{
//   // TODO: copy
//}

// TODO: Uncomment the assignment operator when you need it.
//inline MLBVacation& MLBVacation::operator=(const MLBVacation& rhs)
//{
//   if (this == &rhs) {
//      return *this;
//   }
//
//   // TODO: assignment
//
//   return *this;
//}

#endif // __MLBVACATION_H_INCL__
