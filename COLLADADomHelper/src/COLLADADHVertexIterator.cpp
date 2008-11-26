/*
    Copyright (c) 2008 NetAllied Systems GmbH

    This file is part of COLLADADomHelper.

    Licensed under the MIT Open Source License, 
    for details please see LICENSE file or the website
    http://www.opensource.org/licenses/mit-license.php
*/

#include "COLLADADHStableHeaders.h"
#include "COLLADADHVertexIterator.h"

namespace COLLADADH
{
	//-----------------------------------------------------------------------
    VertexIterator::VertexIterator( const domVertices &vertexElement )
            : mVertexElement( vertexElement )
    {
        mCurrentIndex = 0;
        // get the order of the input.
        const domInputLocal_Array & inputArray = mVertexElement.getInput_array();
        
		for ( daeUInt i = 0; i < inputArray.getCount(); i++ )
        {
			domInputLocal* input = inputArray.get(i);
			daeURI src(*(input->getDAE()));
			mOrder.push_back( OTHER );

            int order = mOrder[ i ];

			if ( strcmp( input->getSemantic(), "POSITION" ) == 0 )
            {
				order |= POINT;
				src = input->getSource();
				src.setContainer(input);
                if ( src.getElement() )
				{
					positions = daeSafeCast<domSource>( src.getElement() );
				}                
            }
			mOrder[ i ] = ( Order ) order;
        }
    }

    //-----------------------------------------------------------------------
    VertexIterator::~VertexIterator()
    {     
    }

    //-----------------------------------------------------------------------
    bool VertexIterator::more()
    {
        bool bRet = false;

		domFloat_arrayRef array = positions->getFloat_array();
        //TODO: Pr�fen des Accessors
        domListOfFloats floats = array->getValue();
        
		if (floats.getCount() > mCurrentIndex)
			bRet = true;
        return bRet;
    }
}