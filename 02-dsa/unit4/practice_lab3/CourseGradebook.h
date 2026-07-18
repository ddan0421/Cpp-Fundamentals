#ifndef COURSEGRADEBOOK_H
#define COURSEGRADEBOOK_H

#include "Gradebook.h"
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

class CourseGradebook : public Gradebook {
protected:
  std::unordered_map<std::string, std::unordered_map<int, double>> assignment;

public:
  virtual ~CourseGradebook() {}

  std::unordered_map<int, double>
  GetAssignmentScores(std::string assignmentName) override {
    if (assignment.count(assignmentName) == 1) {
      return assignment[assignmentName];
    }
    return std::unordered_map<int, double>();
  }

  double GetScore(std::string assignmentName, int studentID) override {
    //
    if (assignment.count(assignmentName) == 1) {
      if (assignment[assignmentName].count(studentID) == 1) {
        return assignment[assignmentName][studentID];
      } else {
        return NAN;
      }
    } else {
      return NAN;
    }
  }

  std::vector<std::string> GetSortedAssignmentNames() override {
    std::vector<std::string> names;
    names.reserve(assignment.size());
    for (const auto &pair : assignment) {
      names.push_back(pair.first);
    }
    std::sort(names.begin(), names.end());
    return names;
  }

  // GetSortedStudentIDs() returns a vector with all distinct student IDs,
  // sorted in ascending order.
  std::vector<int> GetSortedStudentIDs() override {
    std::vector<int> studentID;

    std::unordered_set<int> studentIDSet;

    for (const auto &pair : assignment) {
      for (const auto &studentScores : pair.second) {
        studentIDSet.insert(studentScores.first);
      }
    }
    for (const auto &id : studentIDSet) {
      studentID.push_back(id);
    }
    std::sort(studentID.begin(), studentID.end());

    return studentID;
  }

  // GetStudentScores() gets all scores that exist in the gradebook for the
  // student whose ID equals the studentID parameter. Scores are returned as
  // an unordered_map that maps an assignment name to the student's
  // corresponding score for that assignment.
  std::unordered_map<std::string, double>
  GetStudentScores(int studentID) override {
    std::unordered_map<std::string, double> assignmentScores;
    for (const auto &pair : assignment) {
      for (const auto &studentScores : pair.second) {

        if (studentScores.first == studentID) {
          assignmentScores[pair.first] = studentScores.second;
        }
      }
    }
    return assignmentScores;
  }

  void SetScore(std::string assignmentName, int studentID,
                double score) override {

    assignment[assignmentName][studentID] = score;
  }
};

#endif
