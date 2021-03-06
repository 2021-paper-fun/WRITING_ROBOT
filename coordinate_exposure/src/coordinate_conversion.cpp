#ifndef COORDINATE_EXPOSURE_CONVERSION_H
#define COORDINATE_EXPOSURE_CONVERSION_H

#include <ros/ros.h>
#include <vector>
#include <opencv2/core/core.hpp>
#include <coordinate_exposure/coordinate.h>
#include <coordinate_exposure/coordinate_set.h>
#include <coordinate_exposure/coordinate_sets.h>

#include <coordinate_exposure/coordinate_conversion.h>


//Function to convert msg format coordinate to point_ <double>


void decodeCoordinate(const coordinate_exposure::coordinate& input, cv::Point2d& output)
{
  output.x = input.x;
  output.y = input.y;
}


//Function to convert Point_ <double> to msg_format coordinate


void codeCoordinate(const cv::Point2d& input, coordinate_exposure::coordinate& output)
{
  output.x = input.x;
  output.y = input.y;
  output.header.stamp = ros::Time::now();
}


//Function to convert msg format vector_of_coordinates to vector <point_ <double>>


void decodeCoordinateSet(const coordinate_exposure::coordinate_set& input, std::vector<cv::Point2d>& output)
{
  cv::Point2d current_coordinate;

  for(int p = 0; p < input.data.size(); p++)
  {
    decodeCoordinate(input.data.at(p), current_coordinate);
    output.push_back(current_coordinate);
  }
}


//Function to convert vector <point_ <double>> to msg format vector_of_coordinates


void codeCoordinateSet(const std::vector<cv::Point2d>& input, coordinate_exposure::coordinate_set& output)
{
  coordinate_exposure::coordinate current_coordinate;

  for(int p = 0; p < input.size(); p++)
  {
    codeCoordinate(input.at(p), current_coordinate);
    output.data.push_back(current_coordinate);
    output.header.stamp = ros::Time::now();
  }
}


//Function to convert msg format vector_of_vector_of_coordinates to vector <vector <point_ <double>>>


void decodeCoordinateSets(const coordinate_exposure::coordinate_sets& input, std::vector<std::vector<cv::Point2d> >& output)
{
  std::vector<cv::Point2d> current_coordinates;

  for(int c = 0; c < input.data.size(); c++)
  {
    decodeCoordinateSet(input.data.at(c), current_coordinates);
    output.push_back(current_coordinates);
    current_coordinates.clear();
  }
}


//Function to convert vector <vector <point_ <double>>> to msg format vector_of_vector_of_coordinates


void codeCoordinateSets(const std::vector<std::vector<cv::Point2d> >& input, coordinate_exposure::coordinate_sets& output)
{
  output.data.resize(input.size());

  for(int c = 0; c < input.size(); c++)
  {
    codeCoordinateSet(input.at(c), output.data.at(c));
    output.header.stamp = ros::Time::now();
  }
}

#endif // COORDINATE_EXPOSURE_CONVERSION_H
