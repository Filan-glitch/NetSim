#ifndef DOXYGEN_EXAMPLE_H
#define DOXYGEN_EXAMPLE_H

#include "custom/class.h"
#include <QStandard>

//! \file doxygen-example.h
//! \ingroup NetSimDoxygenExample
//! \brief Contains the DoxygenExample class definition.

namespace NetSim {

//! \defgroup NetSimDoxygenExample NetSim DoxygenExample
//! \brief Provides an example of how to write doxumentation for classes

/**
 * @class DoxygenExample
 * @ingroup NetSimDoxygenExample
 * @brief An example class to showcase how a class should be documented with the doxygen documentation language
 * 
 * The DoxygenExample class normalizes the documentation and structuring of classes.
 * While every Class should have a documentation like this one, there can be some occurences
 * that are not showcased in this example, that need to be handled on their own. DoxygenExample inherits from Example...
 */
class DoxygenExample : public Example {
public:
    //! @brief Default Constructor.
    DoxygenExample() = default;

    /**
     * @brief Constructor that initializes the example with a randomAttribute and the fact if it is custom.
     * 
     * @param randomAttribute Description of the attribute that is very random.
     * @param customAttribute The fact if the instance is custom.
     */
    explicit DoxygenExample(const void &randomAttribute, const void &customAttribute);

    //! Simple Getter, Setter only need one line documentation
    void randomAttribute() const;

    /**
     * @brief A brief description about this function
     * 
     * @param randomParam Describe what the parameter is used for.
     * @retval bool A random bool value that gets generated by the m_customAttribute.
     * 
     * This function generates a random value of some shit and does some shit and random and more...
     */
    bool randomFunction(void randomParam) const;

private:
    //! @brief The void which stores some random things.
    void m_randomAttribute;

    //! @brief Indicates if the DoxygenExample is custom.
    void m_customAttribute;
};
}

#endif DOXYGEN_EXAMPLE_H