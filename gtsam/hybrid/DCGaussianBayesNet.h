/* ----------------------------------------------------------------------------

 * GTSAM Copyright 2010, Georgia Tech Research Corporation,
 * Atlanta, Georgia 30332-0415
 * All Rights Reserved
 * Authors: Frank Dellaert, et al. (see THANKS for the full author list)

 * See LICENSE for the license information

 * -------------------------------------------------------------------------- */

/**
 * @file    DCGaussianMixtureFactor.h
 * @brief   A set of GaussianFactors, indexed by a set of discrete keys.
 * @author  Varun Agrawal
 * @author  Fan Jiang
 * @author  Frank Dellaert
 * @date    December 2021
 */

#pragma once

#include <gtsam/discrete/DiscreteKey.h>
#include <gtsam/inference/BayesNet.h>
#include <gtsam/linear/GaussianConditional.h>

#include <iostream>  // TODO!

namespace gtsam {

/// A set of GaussianConditionals, indexed by a set of discrete variables.
class DCGaussianConditional {
 public:
  using shared_ptr = boost::shared_ptr<DCGaussianConditional>;
  void print(const std::string& s = "DCGaussianConditional",
             const KeyFormatter& formatter = gtsam::DefaultKeyFormatter) const {
    std::cout << (s.empty() ? "" : s + " ") << std::endl;
  }
};

/// Bayes net
class DCGaussianBayesNet : public BayesNet<DCGaussianConditional> {
 public:
  using ConditionalType = DCGaussianConditional;
  using shared_ptr = boost::shared_ptr<DCGaussianBayesNet>;
};

}  // namespace gtsam
