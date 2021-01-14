## WINDOWS BINARIES
- Please download the windows binaries of Fespp in the [release section](https://github.com/F2I-Consulting/fespp/releases) and follow instructions of the README.txt contained in the zip.
- If you want to build Fespp by your own, look below for instructions.

## BUILD dependencies
- [FESAPI v2.0.0.0](https://github.com/F2I-Consulting/fesapi/releases/tag/v2.0.0.0)
- ParaView with same HDF5 libraries used by Fesapi
	 > known to work on Linux and Windows starting from ParaView 5.7.0

## BUILD & INSTALL Fespp
1. **CONFIGURE** Fespp with CMAKE
You should fill in the following variables
   * FESAPI_INCLUDE = path_to_FESAPI_install/include
   * FESAPI_LIBRARY_RELEASE = path_to_FESAPI_install/lib/libFesapiCpp.so
   * ParaView_DIR = path_to_paraview_build
2. **GENERATE** the build solution with CMAKE once the CONFIGURE step is OK
3. **BUILD** the solution generated by CMAKE
4. **COPY** the following built libraries
 
	- in the ParaView bin folder on Linux:
	   - libFesapiCpp.so (from FESAPI install)
	   - libFesapiCpp.so.2.0 (from FESAPI install)
	   - libFesapiCpp.so.2.0.0 (from FESAPI install)
	   - libEPCReader.so (from FESPP install)
	   - libFespp.so (from FESPP install)
   
	- in a ParaView bin\paraview-5.7\plugins\Fespp folder on Windows:
	   - FesapiCpp.2.0.0.0.dll (from FESAPI install)
	   - EPCReader.dll (from FESPP install)
	   - Fespp.dll (from FESPP install)

- **Note 1** : You also need to copy FESAPI dependencies such as hdf5, zlib, szip libraries in the same folder on windows. Or to put them in the (LD_LIBRARY_)PATH.
- **Note 2** : On Linux at least, you need to build Paraview with VTK_MODULE_USE_EXTERNAL_VTK_hdf5=ON and VTK_MODULE_USE_EXTERNAL_VTK_zlib=ON for using the same HDF5 libraries in PV and Fespp. We use statically link HDF5 with FESAPI for our Windows build.

## Execution
1. Only if you use MPI ParaView version, **Run** the **Paraview server** (Caution : use **MPI** build of ParaView!!!) : 
	> mpirun -np 8 ./pvserver
2. **Run** the **ParaView client** : 
	> ./paraview
3. Only if you use MPI ParaView version, **Connect** the **Client to** the **Server**
On client side : File->Connect...  and then fill in the required fields.
4. **Loading** of the **Fespp plugins** (Caution: on **client** and, only if you use MPI ParaView version, **server** sides!!!)
	> Menu Tools->Manage plugins...
	> and then select and Load libFespp.so
5. You can now load a RESQML file (epc document)
	- via epc load manager (blue icon)
