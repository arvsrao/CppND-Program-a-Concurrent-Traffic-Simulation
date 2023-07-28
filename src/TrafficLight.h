#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include <mutex>
#include <deque>
#include <random>
#include <condition_variable>
#include "TrafficObject.h"

// forward declarations to avoid include cycle
class Vehicle;

enum TrafficLightPhase { red, green };

// FP.3 Define a class „MessageQueue“ which has the public methods send and receive. 
// Send should take an rvalue reference of type TrafficLightPhase whereas receive should return this type. 
// Also, the class should define a std::dequeue called _queue, which stores objects of type TrafficLightPhase.
// Also, there should be a std::condition_variable as well as an std::mutex as private members.

template <typename T>
class MessageQueue
{
public:
    T receive();
    void send(T &&msg);

private:
    std::deque<T> _queue;
    std::condition_variable _condition;
    std::mutex _mutex;
};

// FP.1 : Define a class „TrafficLight“ which is a child class of TrafficObject. 
// The class shall have the public methods „void waitForGreen()“ and „void simulate()“ 
// as well as „TrafficLightPhase getCurrentPhase()“, where TrafficLightPhase is an enum that 
// can be either „red“ or „green“. Also, add the private method „void cycleThroughPhases()“. 
// Furthermore, there shall be the private member _currentPhase which can take „red“ or „green“ as its value.

class RandomNumberBetween
{
public:
    RandomNumberBetween(int low, int high);
    int operator()();
private:
    std::mt19937 random_engine_;
    std::uniform_int_distribution<int> distribution_;
};

class TrafficLight : TrafficObject
{
public:
    // constructor / destructor
    TrafficLight();

    // getters / setters
    void toggleTrafficLight();

    // typical behaviour methods
    void waitForGreen();
    void simulate() override;
    TrafficLightPhase getCurrentPhase();


private:
    // typical behaviour methods
    void cycleThroughPhases();

    // FP.4b : create a private member of type MessageQueue for messages of type TrafficLightPhase 
    // and use it within the infinite loop to push each new TrafficLightPhase into it by calling 
    // send in conjunction with move semantics.
    MessageQueue<TrafficLightPhase> _message;
    TrafficLightPhase _currentPhase;
    RandomNumberBetween _randomNumberBetween4AndSix;
};

#endif