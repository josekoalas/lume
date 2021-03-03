//project verse, 2017-2021
//by jose pazos perez
//all rights reserved uwu

#pragma once

#include "dtypes.h"
#include "log.h"

#include "c_collider.h"
#include "c_texture.h"
#include "c_actor.h"
#include "c_tilemap.h"
#include "c_light.h"

#define INVALID_ENTITY Entity::createID(EntityIndex(-1), 0)

namespace Verse
{
    typedef ui32 EntityID;
    const EntityID MAX_ENTITIES = 4096;

    typedef ui8 ComponentID;
    const ComponentID MAX_COMPONENTS = 16;

    typedef std::bitset<MAX_COMPONENTS> Signature;
}

namespace Verse::Entity
{
    typedef ui16 EntityIndex;
    typedef ui16 EntityVersion;

    inline EntityID createID(EntityIndex index, EntityVersion version) { return ((EntityID)index << 16) | ((EntityID)version); };
    inline EntityIndex getIndex(EntityID eid) { return eid >> 16; };
    inline EntityVersion getVersion(EntityID eid) { return (EntityVersion)eid; };

    inline bool isValid(EntityID eid) { return (eid >> 16) != EntityIndex(-1); };
}

namespace Verse::Component
{
    extern ComponentID component_counter;

    template <class T>
    ComponentID getID();

    void registerComponents();
}
