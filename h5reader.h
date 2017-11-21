#include "hdf5.h"
#include <cstdint>
#include <cmath>
#include <vector>
#include <istream>
#include <string>
#include <ctime>

template<typename Real>
struct CalibrationData
{
	Real slope;
	Real offset;

	CalibrationData() :
		slope(NAN),
		offset(NAN)
	{}

	// Allow construction from different precision
	// (e.g. float from double)
	template<typename Other>
	CalibrationData(CalibrationData<Other> _cal) :
		slope(_cal.slope),
		offset(_cal.offset)
	{}
};

template<typename RawType, typename Real>
struct ChannelData
{
	CalibrationData<Real> calibration;
	std::vector<RawType> raw_data;
};

struct Data {
	uint16_t satellite_id;
	std::string satellite_name;
	// Scan start/end time, from the prologue/header and epilogue/trailer
	// We could even get the invididual line scan times,
	// but maybe that's too much
	ChannelData<uint16_t, double> ch04;
	ChannelData<uint16_t, double> ch09;
	uint rows;
	uint cols;
};

class h5Image {
private:
  hid_t       file_id, dataset_id, dataspace;  /* identifiers */
  herr_t      status;
  Data data;
  hsize_t dims[2];
  ChannelData<uint16_t, double> *channel_data;

public:
  h5Image(char *file, char *dataset_path, int ROWS, int COLS){
    /* Open an existing file. */
    this->file_id = H5Fopen(file, H5F_ACC_RDWR, H5P_DEFAULT);

    /* Open an existing dataset. */
    this->dataset_id = H5Dopen2(file_id, dataset_path, H5P_DEFAULT);

    /*status = H5Dread(dataset_id, H5T_NATIVE_INT, H5S_ALL, H5S_ALL, H5P_DEFAULT, dset_data);*/
    this->dataspace = H5Dget_space(dataset_id);

    this->data.rows = ROWS;

    this->data.cols = COLS;

    this->channel_data = &(data.ch04);

    this->status = 0;
  }

  void read(){
    this->channel_data->raw_data.resize(this->data.rows*this->data.cols);
    this->status = H5Dread(this->dataset_id, H5T_NATIVE_USHORT, H5S_ALL, this->dataspace,
      H5P_DEFAULT, this->channel_data->raw_data.data());

    for (unsigned i=0; i<this->channel_data->raw_data.size(); i++)
     std::cout << this->channel_data->raw_data.at(i) << std::endl;

    /* Close the dataset. */
    this->status = H5Dclose(dataset_id);

    /* Close the file. */
    this->status = H5Fclose(file_id);
  }
};
