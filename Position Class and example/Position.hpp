#pragma once

#include <iostream>
#include <cmath>

/**
 * @brief Generalized Pure Virtual Position class
 */
class Position{

    public:

    /**
     * @brief Destructor for Position class
     */
    virtual ~Position(){};

    /**
     * @brief Virtual clone method for Position class 
     * @return A pointer to a copy of the object   
     */
    virtual Position* clone() const = 0;

    /**
     * @brief Get x coordinate (Cartesian) 
     * @return x coordinate (Cartesian) 
     * @note This method is pure virtual and must be redefined in derived classes
     */
    virtual double getX() const = 0;

    /**
     * @brief Get y coordinate (Cartesian) 
     * @return y coordinate (Cartesian) 
     * @note This method is pure virtual and must be redefined in derived classes
     */
    virtual double getY() const = 0;

    /**
     * @brief Get z coordinate (Cartesian) 
     * @return z coordinate (Cartesian) 
     * @note This method is pure virtual and must be redefined in derived classes
     */
    virtual double getZ() const = 0;

    /**
     * @brief Get r coordinate (Spherical) 
     * @return r coordinate (Spherical) 
     * @note This method is pure virtual and must be redefined in derived classes
     */
    virtual double getR() const = 0;

     /**
     * @brief Get theta coordinate (Spherical) 
     * @return theta coordinate (Spherical) 
     * @note This method is pure virtual and must be redefined in derived classes
     * @note theta is the polar angle
     * @note theta is in the range [0,pi]
     * @note theta is measured from the z axis
     * @note theta is positive in the counter-clockwise direction
     * @note theta is zero when z>0
     * @note theta is pi when z<0
     * @note theta is undefined when z=0
     */
    virtual double getTheta() const = 0;

    /**
     * @brief Get phi coordinate (Spherical) 
     * @return phi coordinate (Spherical) 
     * @note This method is pure virtual and must be redefined in derived classes
     * @note phi is the azimuthal angle
     * @note phi is in the range [0,2pi]
     * @note phi is measured from the x axis
     * @note phi is positive in the counter-clockwise direction
     * @note phi is zero when x>0 and y=0
     * @note phi is pi/2 when x=0 and y>0
     * @note phi is pi when x<0 and y=0
     * @note phi is 3pi/2 when x=0 and y<0
     * @note phi is undefined when x=0 and y=0
     */
    virtual double getPhi() const = 0;

    /**
     * @brief Get rho coordinate (Cylindrical) 
     * @return rho coordinate (Cylindrical) 
     * @note This method is pure virtual and must be redefined in derived classes
     * @note rho is the radial distance from the z axis
     * @note rho is in the range [0,inf)
     * @note rho is positive
     * @note rho is zero when x=0 and y=0
     * @note rho is undefined when z=0
     */
    virtual double getRho() const = 0;


    /**
     * @brief Get distance between two points
     * @param p Position of the second point
     * @return distance between two points
     * @note This method is pure virtual and must be redefined in derived classes
     * @note This method is const
     * @note This method is inline
     * @note This method is virtual
     * @note The distance is calculated as:
     * @f[  d = \sqrt{(x_1-x_2)^2+(y_1-y_2)^2+(z_1-z_2)^2}  @f]
     */
    virtual double Distance(const Position * p) const= 0;

    /**
     * @brief Print the coordinates of the point
     * @note This method is pure virtual and must be redefined in derived classes
     * @note This method is const
     * @note This method is inline
     * @note This method is virtual
     * @note The coordinates are printed to the standard output
     * @note The coordinates are printed as:
     * @f[  (x,y,z)  @f]
     * @f[  (r,\theta,\phi)  @f]
     * @f[  (r,\theta,z)   @f]
     */
    virtual void Print() const =0;

    //virtual void Immersion() const = 0;
};

//*********************************************************************************************************************
// Cartesian coordinates class (x,y,z) 
//*********************************************************************************************************************

/**
 * @brief Cartesian coordinates class (x,y,z) 
 * @note This class is derived from the Position class
 */
class Cartesian: public Position {

    private:
    double m_x; ///< x coordinate
    double m_y; ///< y coordinate
    double m_z; ///< z coordinate

    public:
    //******************************************************
    // Constructors
    //******************************************************
    
    /**
     * @brief Default constructor for Cartesian class: set all coordinates to zero
     */
    Cartesian();

    /**
     * @brief Constructor for Cartesian class: set all coordinates to the given values
     * @param x x coordinate 
     * @param y y coordinate
     * @param z z coordinate
     */
    Cartesian(double x,double y,double z);

    /**
     * @brief Move constructor for Cartesian class
     * @param p Cartesian to be moved
     */
    Cartesian(Cartesian&& p);

    /**
     * @brief Copy constructor for Cartesian class
     * @param p Cartesian to be copied
     */
    Cartesian(const Cartesian& p);

    /**
     * @brief clone method for Cartesian class
     * 
     * @return Cartesian* A pointer to a copy of the object
     */
    Cartesian* clone() const override;


    /**
     * @brief Virtual destructor for Cartesian class
     */
    ~Cartesian() override;

    //******************************************************
    // Virtual methods inherited from Position
    //******************************************************

    /**
     * @brief Get x coordinate
     * @return x coordinate in Cartesian coordinates
     */
    double getX() const override;

    /**
     * @brief Get y coordinate
     * @return y coordinate in Cartesian coordinates
     */
    double getY() const override;

    /**
     * @brief Get z coordinate
     * @return z coordinate in Cartesian coordinates
     */
    double getZ() const override;
    
    /**
     * @brief Get Radius in spherical coordinates
     * @return Radius in spherical coordinates
     */
    double getR() const override;

    /**
     * @brief Get Polar angle in spherical coordinates
     * @return Polar angle in spherical coordinates
     */
    double getTheta() const override;

    /**
     * @brief Get Azimuthal angle in spherical coordinates
     * @return Azimuthal angle in spherical coordinates or in cylindrical coordinates
     */
    double getPhi() const override;

    /**
     * @brief Get Radius in cylindrical coordinates
     * @return Radius in cylindrical coordinates 
     */
    double getRho() const override;

    /**
     * @brief Get distance between two points
     * @param p Generalised Position of the second point
     * @return distance between two points
     */
    double Distance(const Position* r) const override;

    /**
     * @brief Print the coordinates of the point as: (x, y, z)
     * @note The coordinates are printed to the standard output
     * @note The coordinates are printed as:
     * @f[  (x,y,z)  @f]
     */
    void Print() const override;


    //******************************************************
    // Methods
    //******************************************************
    /**
     * @brief Get distance between two points
     * @param x x coordinate of the second point
     * @param y y coordinate of the second point
     * @param z z coordinate of the second point
     * @return distance between two points
     */
    double Distance(double x,double y,double z) const;

    /**
     * @brief Set the first coordinate of the point to the given value 
     * @param x x coordinate of the point
     */
    void SetX(double x);

    /**
     * @brief Set the second coordinate of the point to the given value 
     * @param y y coordinate of the point
     */
    void SetY(double y);

    /**
     * @brief Set the third coordinate of the point to the given value 
     * @param z z coordinate of the point
     */
    void SetZ(double z);

    /**
     * @brief Set the coordinates of the point to the given values 
     * @param x x coordinate of the point
     * @param y y coordinate of the point
     * @param z z coordinate of the point
     */
    void Set(double x,double y,double z);

    

};


//*********************************************************************************************************************
// Spherical coordinates class (r,theta,phi)
//*********************************************************************************************************************

/**
 * @brief Spherical coordinates class (r,theta,phi)
 * @note This class is derived from the Position class
 */
class Spherical: public Position{
private:
    double m_r; ///< Radius in spherical coordinates
    double m_theta; ///< Polar angle in spherical coordinates
    double m_phi; ///< Azimuthal angle in spherical coordinates

public:

    //******************************************************
    // Constructors
    //******************************************************

    /**
     * @brief Default constructor for Spherical class: set all coordinates to zero
     */
    Spherical();

    /**
     * @brief Constructor for Spherical class: set all coordinates to the given values
     * @param r Radius in spherical coordinates
     * @param theta Polar angle in spherical coordinates
     * @param phi Azimuthal angle in spherical coordinates
     */
    Spherical(double r,double theta,double phi);

    /**
     * @brief Move constructor for Spherical class
     * @param p Spherical to be moved 
     * @note This constructor is deleted because the move constructor for the Position class is deleted
     */
    Spherical(Spherical&& p);

    /**
     * @brief Copy constructor for Spherical class
     * @param p Spherical to be copied
     */
    Spherical(const Spherical& p);

    /**
     * @brief clone method for Spherical class
     * 
     * @return Spherical* A pointer to a copy of the object
     */
    Spherical* clone() const override;


    /**
     * @brief Virtual destructor for Spherical class
     * @note This destructor is virtual because the destructor for the Position class is virtual
     */
    ~Spherical() override;

    //******************************************************
    // Virtual methods inherited from Position
    //******************************************************

    /**
     * @brief Get x coordinate
     * @return x coordinate in Cartesian coordinates
     */
    double getX() const override;

    /**
     * @brief Get y coordinate
     * @return y coordinate in Cartesian coordinates
     */
    double getY() const override;

    /**
     * @brief Get z coordinate
     * @return z coordinate in Cartesian coordinates
     */

    double getZ() const override;

    /**
     * @brief Get Radius in spherical coordinates
     * @return Radius in spherical coordinates
     */
    double getR() const override;

    /**
     * @brief Get Polar angle in spherical coordinates
     * @return Polar angle in spherical coordinates
     */
    double getTheta() const override;

    /**
     * @brief Get Azimuthal angle in spherical coordinates
     * @return Azimuthal angle in spherical coordinates or in cylindrical coordinates
     */
    double getPhi() const override;

    /**
     * @brief Get Radius in cylindrical coordinates
     * @return Radius in cylindrical coordinates
     */
    double getRho() const override;

    /**
     * @brief Get distance between two points
     * @param p Generalised Position of the second point
     * @return distance between two points
     */
    double Distance(const Position* p) const override;

    /**
     * @brief Print the coordinates of the point as: (r,theta,phi)
     * @note The coordinates are printed to the standard output
     * @note The coordinates are printed as:
     * @f[  (r,\theta,\phi)  @f]
     */
    void Print() const override;

    //******************************************************
    // Methods
    //******************************************************

    /**
     * @brief Get distance between two points
     * @param r Radius in spherical coordinates of the second point
     * @param theta Polar angle in spherical coordinates of the second point
     * @param phi Azimuthal angle in spherical coordinates of the second point
     * @return distance between two points
     * @note The distance is calculated using the formula:
     * @f[  d = \sqrt{r^2 + r'^2 - 2r r'\[\sin(theta)\sin(theta')(\cos(\theta - \theta')) + \cos(theta)\cos(theta') }  @f]
     */
    double Distance(double r,double theta,double phi) const;

    /**
     * @brief Set the first coordinate of the point to the given value 
     * @param r Radius in spherical coordinates
     */
    void SetR(double r);

    /**
     * @brief Set the second coordinate of the point to the given value 
     * @param theta Polar angle in spherical coordinates
     */
    void SetTheta(double theta);

    /**
     * @brief Set the third coordinate of the point to the given value 
     * @param phi Azimuthal angle in spherical coordinates
     */
    void SetPhi(double phi);

    /**
     * @brief Set the coordinates of the point to the given values 
     * @param r Radius in spherical coordinates
     * @param theta Polar angle in spherical coordinates
     * @param phi Azimuthal angle in spherical coordinates
     */
    void Set(double r,double theta,double phi);

};


//*********************************************************************************************************************
// Cylindrical coordinates class (rho,phi,z)
//*********************************************************************************************************************

/**
 * @brief Cylindrical coordinates class (rho,phi,z)
 * @note This class is derived from the Position class
 */
class Cylindrical: public Position{
private:
    double m_rho; ///< Radius in cylindrical coordinates
    double m_phi; ///< Azimuthal angle in cylindrical coordinates
    double m_z; ///< z coordinate in cylindrical coordinates

public:
    
        //******************************************************
        // Constructors
        //******************************************************
    
        /**
        * @brief Default constructor for Cylindrical class: set all coordinates to zero
        */
        Cylindrical();
    
        /**
        * @brief Constructor for Cylindrical class: set all coordinates to the given values
        * @param rho Radius in cylindrical coordinates
        * @param phi Azimuthal angle in cylindrical coordinates
        * @param z z coordinate in cylindrical coordinates
        */
        Cylindrical(double rho,double phi,double z);
    
        /**
        * @brief Move constructor for Cylindrical class
        * @param p Cylindrical to be moved 
        * @note This constructor is deleted because the move constructor for the Position class is deleted
        */
        Cylindrical(Cylindrical&& p);

        /**
         * @brief Copy constructor for Cylindrical class
         * 
         * @param p Cylindrical to be copied
         */
        Cylindrical(const Cylindrical& p);

        /**
         * @brief clone method for Cylindrical class
         * 
         * @return Cylindrical* A pointer to a copy of the object
         */
        Cylindrical* clone() const override;
    
        /**
        * @brief Virtual destructor for Cylindrical class
        * @note This destructor is virtual because the destructor for the Position class is virtual
        */
        ~Cylindrical() override;
    
        //******************************************************
        // Virtual methods inherited from Position
        //******************************************************
    
        /**
        * @brief Get x coordinate
        * @return x coordinate in Cartesian coordinates
        */
        double getX() const override;
    
        /**
        * @brief Get y coordinate
        * @return y coordinate in Cartesian coordinates
        */
        double getY() const override;
    
        /**
        * @brief Get z coordinate
        * @return z coordinate in Cartesian coordinates
        */
        double getZ() const override;
    
        /**
        * @brief Get Radius in spherical coordinates
        * @return Radius in spherical coordinates
        */
        double getR() const override;
    
        /**
        * @brief Get Polar angle in spherical coordinates
        * @return Polar angle in spherical coordinates
        */
        double getTheta() const override;
    
        /**
        * @brief Get Azimuthal angle in spherical coordinates
        * @return Azimuthal angle in spherical coordinates or in cylindrical coordinates
        */
        double getPhi() const override;
    
        /**
        * @brief Get Radius in cylindrical coordinates
        * @return Radius in cylindrical coordinates
        */
        double getRho() const override;
    
        /**
        * @brief Get distance between two points
        * @param p Generalised Position of the second point
        * @return distance between two points
        */
        double Distance(const Position* p) const override;
    
        /**
        * @brief Print the coordinates of the point as: (r, theta, phi) 
        * @note The coordinates are printed to the standard output
        * @note The coordinates are printed as:
        * @f[  (r,\theta,\phi)  @f]
        */
        void Print() const override;

        //******************************************************
        // Methods
        //******************************************************

        /**
         * @brief Get distance between two points
         * @param rho Radius in cylindrical coordinates of the second point
         * @param phi Azimuthal angle in cylindrical coordinates of the second point
         * @param z z coordinate in cylindrical coordinates of the second point
         * @return distance between two points
         * @note The distance is calculated using the formula:
         * @f[  d = \sqrt{r^2 + r'^2 - 2r r'\cos(\phi - \phi') + (z-z')^2}  @f]
         */
        double Distance(double rho,double phi,double z) const;

        /**
         * @brief Set the first coordinate of the point to the given value 
         * @param rho Radius in cylindrical coordinates
         */
        void SetRho(double rho);

        /**
         * @brief Set the second coordinate of the point to the given value 
         * @param phi Azimuthal angle in cylindrical coordinates
         */
        void SetPhi(double phi);

        /**
         * @brief Set the third coordinate of the point to the given value 
         * @param z z coordinate in cylindrical coordinates
         */
        void SetZ(double z);

        /**
         * @brief Set the coordinates of the point to the given values 
         * @param rho Radius in cylindrical coordinates
         * @param phi Azimuthal angle in cylindrical coordinates
         * @param z z coordinate in cylindrical coordinates
         */
        void Set(double rho,double phi,double z);

};