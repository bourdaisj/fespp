﻿/*-----------------------------------------------------------------------
Licensed to the Apache Software Foundation (ASF) under one
or more contributor license agreements.  See the NOTICE file
distributed with this work for additional information
regarding copyright ownership.  The ASF licenses this file
to you under the Apache License, Version 2.0 (the
"License"; you may not use this file except in compliance
with the License.  You may obtain a copy of the License at

  http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing,
software distributed under the License is distributed on an
"AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
KIND, either express or implied.  See the License for the
specific language governing permissions and limitations
under the License.
-----------------------------------------------------------------------*/
#ifndef __ResqmlAbstractRepresentationTovtkPartitionedDataSet__h__
#define __ResqmlAbstractRepresentationTovtkPartitionedDataSet__h__

// include system
#include <string>

// include VTK library
#include <vtkSmartPointer.h>
#include <vtkPartitionedDataSet.h>

// include F2i-consulting Energistics Standards API
#include <fesapi/resqml2/AbstractRepresentation.h>

class vtkUnstructuredGrid;

/** @brief	transform a RESQML abstract representation to vtkPartitionedDataSet
 */
class ResqmlAbstractRepresentationToVtkPartitionedDataSet
{
public:
	/**
	 * Constructor
	 */
	ResqmlAbstractRepresentationToVtkPartitionedDataSet(RESQML2_NS::AbstractRepresentation *abstract_representation, int proc_number = 0, int max_proc = 1);

	/**
	 * Destructor
	 */
	virtual ~ResqmlAbstractRepresentationToVtkPartitionedDataSet() = default;

	/**
	 * load VtkPartitionedDataSet with resqml data
	 */
	virtual void loadVtkObject() = 0;
	/**
	 * unload VtkPartitionedDataSet
	 */
	void unloadVtkObject();

	/**
	 * add a resqml property to VtkPartitionedDataSet
	 */
	void addDataArray(const std::string &uuid, int patch_index = 0);

	/**
	 * remove a resqml property to VtkPartitionedDataSet
	 */
	void deleteDataArray(const std::string &uuid);

	/**
	 * return the vtkPartitionedDataSet of resqml representation
	 */
	vtkSmartPointer<vtkPartitionedDataSet> getOutput() const { return vtkData; }

	/**
	*
	*/
	void registerSubRep();
	void unregisterSubRep();
	unsigned int subRepLinkedCount();

	/**
*
*/
	std::string getUuid() const;
	

protected:

	unsigned int subrep_pointer_on_points_count;

	uint64_t pointCount = 0;
	uint32_t iCellCount = 0; // = cellcount if not ijkGrid
	uint32_t jCellCount = 1;
	uint32_t kCellCount = 1;
	uint32_t initKIndex = 0;
	uint32_t maxKIndex = 0;

	bool isHyperslabed = false;

	int procNumber;
	int maxProc;

	RESQML2_NS::AbstractRepresentation const* resqmlData;

	vtkSmartPointer<vtkPartitionedDataSet> vtkData;
	std::unordered_map<std::string, class ResqmlPropertyToVtkDataArray *> uuidToVtkDataArray;

	/**
	 * Insert a new VTK wedge or pyramid corresponding to a particular RESQML cell
	 *
	 * @param unstructuredGridRep				The RESQML UnstructuredGridRepresentation which contains the cell to map and to insert in the VTK UnstructuredGrid
	 * @param cumulativeFaceCountPerCell		The cumulative count of faces for each cell of the RESQML UnstructuredGridRepresentation.
	 * @param cellFaceNormalOutwardlyDirected	Indicates for each cell face of the RESQML UnstructuredGridRepresentation if its normal using the right hand rule is outwardly directed.
	 * @param cellIndex							The index of the RESQML cell in the RESQML UnstructuredGridRepresentation to be mapped and inserted in the VTK UnstructuredGrid.
	 */
	void cellVtkWedgeOrPyramid(vtkSmartPointer<vtkUnstructuredGrid> vtk_unstructuredGrid,
		const RESQML2_NS::UnstructuredGridRepresentation *unstructuredGridRep,
		ULONG64 const *cumulativeFaceCountPerCell,
		unsigned char const *cellFaceNormalOutwardlyDirected,
		ULONG64 cellIndex);
};
#endif
