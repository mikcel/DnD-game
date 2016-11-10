//! @file 
//! @brief Header file for the Observer class 
//!
#pragma once

class Observer
{
public:
	virtual void update() = 0; //! Pure virtual function update of an Observer
};