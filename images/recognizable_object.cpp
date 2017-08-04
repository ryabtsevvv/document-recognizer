#include "recognizable_object.hpp"

RecognizableObject::RecognizableObject():
  state_(State::New)
{}

bool RecognizableObject::isRecognized() const
{
  return state_ == State::Recognized;
}

bool RecognizableObject::isUnrecognized() const
{
  return state_ != State::Recognized;
}
