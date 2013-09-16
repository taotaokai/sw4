#ifndef MATERIALPARAMETERIZATION_H
#define MATERIALPARAMETERIZATION_H

#include <vector>
#include <Sarray.h>

class EW;

class MaterialParameterization
{
protected:
   int m_myrank, m_nmd, m_nms, m_nmd_global;
   EW* m_ew;
   char* m_filename;
public:
   MaterialParameterization( EW* a_ew, char* fname );
   virtual void get_material( int nmd, double* xmd, int nms, double* xms, std::vector<Sarray>& a_rho,
			      std::vector<Sarray>& a_mu, std::vector<Sarray>& a_lambda )=0;
   virtual void get_parameters( int nmd, double* xmd, int nms, double* xms, std::vector<Sarray>& a_rho, 
				std::vector<Sarray>& a_mu, std::vector<Sarray>& a_lambda )=0;
   virtual void get_gradient( int nmd, double* xmd, int nms, double* xms, double* dfs, double* dfm,
			      std::vector<Sarray>& a_gradrho, std::vector<Sarray>& a_gradmu,
			      std::vector<Sarray>& a_gradlambda )=0;
   //   virtual void perturb_material( int ip, int jp, int kp, int grid, int var, double h, double* xs, double* xm ) = 0;
   virtual ssize_t parameter_index( int ip, int jp, int kp, int grid, int var )=0;
   virtual ssize_t local_index( size_t ind_global )=0;
   void get_nr_of_parameters( int& nms, int& nmd, int& nmd_global ) const;
   void parameters_from_basematerial( int nmd, double* xmd, int nms, double* xms );
   void store_material( std::vector<Sarray>& a_rho, std::vector<Sarray>& a_mu, std::vector<Sarray>& a_lambda );
   void constrain_material( int nmd, double* xmd, int nms, double* xms );
   void write_parameters( const char* filename, int nms, double* xms ); // Only shared parameters for now
   void read_parameters( const char* filename, int nms, double* xms ); // Only shared parameters for now
   void write_parameters( int nms, double* xms ); // Only shared parameters for now
   void read_parameters( int nms, double* xms ); // Only shared parameters for now
};

#endif