/*-----------------------------------------------------------------------
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
#ifndef __ResqmlDataRepositoryToVtkPartitionedDataSetCollection_h
#define __ResqmlDataRepositoryToVtkPartitionedDataSetCollection_h

// include system
#include <string>
#include <map>
#include <set>

#include <vtkSmartPointer.h>
#include <vtkPartitionedDataSetCollection.h>
#include <vtkMultiProcessController.h>

#ifdef WITH_ETP
#include <fetpapi/etp/ClientSessionLaunchers.h>
#endif

namespace common
{
	class DataObjectRepository;
}

namespace resqml2
{
	class AbstractRepresentation;
}

class ResqmlAbstractRepresentationToVtkDataset;

/**
 * @brief	class description.
 */
class ResqmlDataRepositoryToVtkPartitionedDataSetCollection
{
public:
	ResqmlDataRepositoryToVtkPartitionedDataSetCollection();
	~ResqmlDataRepositoryToVtkPartitionedDataSetCollection();
	// --------------- PART: TreeView ---------------------
	vtkDataAssembly *GetAssembly() { return output->GetDataAssembly(); }

	//---------------------------------

	// for EPC reader
	std::string addFile(const char *file);

	// for ETP connection
	std::string connect(const std::string etp_url, const std::string data_partition,const std::string auth_connection);

	// Wellbore Options
	void setMarkerOrientation(bool orientation);
	void setMarkerSize(int size);

	vtkPartitionedDataSetCollection *getVtkPartitionedDatasSetCollection(const double time);

	std::vector<double> getTimes() { return times_step; }

	/**
	* @return selection parent
	*/
	std::string selectNodeId(int node);
	void clearSelection();

private:
	int addNodeGroup(std::string name, int idNode); // return: idNode for the groupName

	std::string buildDataAssemblyFromDataObjectRepo(const char *fileName);

	std::string searchPolylines(const std::string &fileName);
	std::string searchUnstructuredGrid(const std::string &fileName);
	std::string searchTriangulated(const std::string &fileName);
	std::string searchGrid2d(const std::string &fileName);
	std::string searchIjkGrid(const std::string &fileName);
	std::string searchWellboreTrajectory(const std::string &fileName);
	std::string searchRepresentations(resqml2::AbstractRepresentation *representation, int idNode = 0 /* 0 is root's id*/);

	std::string searchSubRepresentation(resqml2::AbstractRepresentation *representation, vtkDataAssembly *assembly, int node_parent);
	std::string searchTimeSeries(const std::string &fileName);

	std::string searchProperties(resqml2::AbstractRepresentation *representation, vtkDataAssembly *assembly, int node_parent);

	void selectNodeIdParent(int node);
	void selectNodeIdChildren(int node);

	ResqmlAbstractRepresentationToVtkDataset *loadToVtk(std::string uuid, double time);

	std::string changeInvalidCharacter(std::string text);
	int searchNodeByUuid(const std::string &uuid);

	bool markerOrientation;
	int markerSize;

	common::DataObjectRepository *repository;

	vtkSmartPointer<vtkPartitionedDataSetCollection> output;

	std::map<int, std::string> nodeId_to_uuid;									// index of VtkDataAssembly to Resqml uuid
	std::map<int, ResqmlAbstractRepresentationToVtkDataset *> nodeId_to_resqml; // index of VtkDataAssembly to ResqmlAbstractRepresentationToVtkDataset

	//\/          uuid             title            index        prop_uuid
	std::map<std::string, std::map<std::string, std::map<double, std::string>>> timeSeries_uuid_and_title_to_index_and_properties_uuid;

	std::set<int> current_selection;
	std::set<int> old_selection;

	// time step values
	std::vector<double> times_step;
#ifdef WITH_ETP
	std::shared_ptr<ETP_NS::PlainClientSession> session;
#endif

};
#endif
