#ifndef INC_2DGAME_ECS_H
#define INC_2DGAME_ECS_H
#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>
using namespace std;


/// ENTITY COMPONENT SYSTEM

class Component;
class Entity;
class Manager;


///Typedef for a Component ID type:
using ComponentID = size_t;

using Group = size_t;


///Returns current value of lastID and increments it by one.
inline ComponentID getNewComponentTypeID(){

    static ComponentID lastID = 0u;

    return lastID++;
}

/// Returns NewComponentTypeID. Takes component as template parameter. If called with same
/// type T will return same value.
/**
 *
 * @tparam T
 * @return
 */

template < typename T > inline ComponentID getComponentTypeID() noexcept {

    static ComponentID typeID = getNewComponentTypeID();
    return typeID;
}

///Checks if Entity has component attached

constexpr size_t maxComponents = 32;
constexpr size_t maxGroups = 32;

using ComponentBitSet = bitset< maxComponents >;
using GroupBitset = bitset < maxGroups >;

/// Array of unique pointer to component. 0 points to component of type 0 etc.
using ComponentArray = array< Component * , maxComponents >;
/// component parent class
class Component{

public:

    ///Pointer to parent entity.
    Entity * entity;

    virtual void Init() {}
    virtual void Update() {}
    virtual void Draw () {}

    ///memory managed correctly with virtual destructor
    virtual ~Component(){}

};
/// Entity Parent class
class Entity {

private:

    Manager & manager;

    /// keep track of state of entity
    bool active {true};

    ///stores components inside entity with vector of unique pointer.
    vector < unique_ptr < Component > > components;

    ComponentArray componentArray;
    ComponentBitSet componentBitSet;
    GroupBitset groupBitset;


public:

    Entity ( Manager & mManager ) : manager ( mManager ){}

    void Update(){

        for( auto & c : components ) c -> Update();
    }

    void Draw(){

        for( auto & c : components ) c -> Draw();

    }
    ///methods for querieing entity's state
    bool isActive() const { return active; }
    void Destroy(){ active = false; }
    bool hasGroup ( Group mGroup ) { return groupBitset[mGroup]; }


    void addGroup( Group mGroup );

    /// Delete entity of group. automatically removes entity from wrong
    /// containers during Refresh.
    /**
     *
     * @param mGroup
     */

    void delGroup ( Group mGroup ){ groupBitset[mGroup] = false; }

    /**
     *
     * @tparam T
     * @return
     */
    template < typename T > bool hasComponent() const {
        
        return componentBitSet[ getComponentTypeID< T >() ];
    }

    /// template for adding components. will take any ammount of args.
    /// forwards all arguements passed to addcomponent method  to constructer
    ///  of component.  not stored heap allocated components in variable c.
    /**
     *
     * @tparam T
     * @tparam TArgs
     * @param mArgs
     * @return
     */
    template < typename T , typename... TArgs >
            T& addComponent( TArgs&&... mArgs ){
        
        T * c ( new T ( forward < TArgs > ( mArgs )...) );

        /// set parent entity of constructor to current entity, access with 'this' pointer

        c -> entity = this;


        /// wrap raw pointer into unique. and move to components vector
        unique_ptr < Component > uPtr { c };
        components.emplace_back( move ( uPtr ) );

        componentArray[ getComponentTypeID < T > () ] = c;
        componentBitSet[ getComponentTypeID < T > () ] = true;

        /// Called after adding component to entity;
        c -> Init();

        /// Dereference pointer to get reference to component.
        return * c;
    }

    /**
     *
     * @tparam T
     * @return
     */
    template < typename T > T & getComponent() const {
        auto ptr ( componentArray[ getComponentTypeID < T > () ] );

        return * static_cast < T * > ( ptr );

    }

};

/// manager parent class
class Manager {

private:

    /// storage for entities. vector of enitity pointers(entities) and an array
    /// of vectors (grouped entities).

    vector < unique_ptr < Entity > > entities;
    array < vector < Entity * > , maxGroups > groupedEntities;

public:


    void Update(){
        for ( auto & e : entities ) e -> Update();
    }

    void Draw(){
        for ( auto & e : entities ) e -> Draw();
    }

    /// removes all entities that are not active in entities vector. nested for loop
    /// iterates through array of vectors ( groupedEntities ). Always called before Update.
    void Refresh(){

        for ( auto i (0u) ; i < maxGroups ; i++ ){

            auto & v ( groupedEntities[i] );

            v.erase( remove_if ( begin( v ) , end( v ) , [i] ( Entity * mEntity ) {

                return !mEntity -> isActive() || !mEntity -> hasGroup( i );

            } ) , end( v ) );

        }
        entities.erase( remove_if( begin( entities ) , end( entities ) ,
        []( const unique_ptr < Entity > & mEntity )
        { return !mEntity -> isActive(); }) ,
        end( entities ));
    }

    void AddToGroup ( Entity * mEntity , Group mGroup ){

        groupedEntities[ mGroup ].emplace_back( mEntity );

    }

    vector < Entity * > & getGroup ( Group mGroup ){

        return groupedEntities[ mGroup ];
    }

    /// returns reference to newly added entity. allocates entity on heap. wraps
    /// into unique pointer and then places back into entities vector.
    /**
     *
     * @return
     */
    Entity & addEntity(){
        Entity * e = new Entity ( * this );
        unique_ptr < Entity > uPtr { e };
        entities.emplace_back( move( uPtr ));

        return * e;
    }
};

/// Inspired by https://vittorioromeo.info/

#endif //INC_2DGAME_ECS_H
