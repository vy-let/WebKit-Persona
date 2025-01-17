/*
 * Copyright (C) 2011, 2013-2015 Apple Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE. 
 */

#ifndef StructureSet_h
#define StructureSet_h

#include "ArrayProfile.h"
#include "SpeculatedType.h"
#include "Structure.h"
#include "DumpContext.h"
#include <wtf/TinyPtrSet.h>

namespace JSC {

namespace DFG {
class StructureAbstractValue;
struct AbstractValue;
}

class StructureSet : public TinyPtrSet<Structure*> {
public:
    // I really want to do this:
    // using TinyPtrSet::TinyPtrSet;
    //
    // But I can't because Windows.
    
    StructureSet()
    {
    }
    
    StructureSet(Structure* structure)
        : TinyPtrSet(structure)
    {
    }
    
    ALWAYS_INLINE StructureSet(const StructureSet& other)
        : TinyPtrSet(other)
    {
    }
    
    Structure* onlyStructure() const
    {
        return onlyEntry();
    }
    
#if ENABLE(DFG_JIT)
    void filter(const DFG::StructureAbstractValue&);
    void filter(SpeculatedType);
    void filterArrayModes(ArrayModes);
    void filter(const DFG::AbstractValue&);
#endif // ENABLE(DFG_JIT)
    
    SpeculatedType speculationFromStructures() const;
    ArrayModes arrayModesFromStructures() const;
    
    void dumpInContext(PrintStream&, DumpContext*) const;
    void dump(PrintStream&) const;
};

} // namespace JSC

#endif // StructureSet_h
