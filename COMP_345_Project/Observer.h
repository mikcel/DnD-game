//!
//! @file 
//! @brief Header file for Observer class
#pragma once

//! Abstract Class that define the observer
class Observer{
	public:
		~Observer(); //! Destructor
		virtual void Update() = 0; //! Pure virtual method
	protected:
		Observer(); //! Constructor
};