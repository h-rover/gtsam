/*
 * CalibratedCamera.h
 *
 *  Created on: Aug 17, 2009
 *      Author: dellaert
 */

#ifndef CalibratedCAMERA_H_
#define CalibratedCAMERA_H_

#include <gtsam/geometry/Pose2.h>
#include <gtsam/geometry/Pose3.h>

namespace gtsam {

	class Point2;

	/**
	 * A Calibrated camera class [R|-R't], calibration K=I.
	 * If calibration is known, it is more computationally efficient
	 * to calibrate the measurements rather than try to predict in pixels.
	 */
	class CalibratedCamera {
	private:
		Pose3 pose_; // 6DOF pose

	public:
		CalibratedCamera();
		CalibratedCamera(const Pose3& pose);
		CalibratedCamera(const Vector &v) ;
		virtual ~CalibratedCamera();

		inline const Pose3& pose() const {	return pose_; }
		bool equals (const CalibratedCamera &camera, double tol = 1e-9) const {
			return pose_.equals(camera.pose(), tol) ;
		}

		inline const CalibratedCamera compose(const CalibratedCamera &c) const {
			return CalibratedCamera( pose_ * c.pose() ) ;
		}

		inline const CalibratedCamera inverse() const {
			return CalibratedCamera( pose_.inverse() ) ;
		}

		inline static size_t dim() { return 6 ; }

		/**
		 * Create a level camera at the given 2D pose and height
		 * @param pose2 specifies the location and viewing direction
		 * (theta 0 = looking in direction of positive X axis)
		 */
		static CalibratedCamera level(const Pose2& pose2, double height);

		/* ************************************************************************* */
		// measurement functions and derivatives
		/* ************************************************************************* */

		/**
		 * This function receives the camera pose and the landmark location and
		 * returns the location the point is supposed to appear in the image
		 * @param camera the CalibratedCamera
		 * @param point a 3D point to be projected
		 * @return the intrinsic coordinates of the projected point
		 */
		Point2 project(const Point3& point,
			    boost::optional<Matrix&> D_intrinsic_pose = boost::none,
			    boost::optional<Matrix&> D_intrinsic_point = boost::none) const;

		/**
		 * projects a 3-dimensional point in camera coordinates into the
		 * camera and returns a 2-dimensional point, no calibration applied
		 * With optional 2by3 derivative
		 */
		static Point2 project_to_camera(const Point3& cameraPoint,
				boost::optional<Matrix&> H1 = boost::none);

		/**
		 * backproject a 2-dimensional point to a 3-dimension point
		 */
		static Point3 backproject_from_camera(const Point2& p, const double scale);

private:
	    /** Serialization function */
	    friend class boost::serialization::access;
	    template<class Archive>
	    void serialize(Archive & ar, const unsigned int version) {
	      ar & BOOST_SERIALIZATION_NVP(pose_);
	    }

	};
}

#endif /* CalibratedCAMERA_H_ */
