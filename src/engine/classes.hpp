#ifndef __CLASSES_HPP__
#define __CLASSES_HPP__

typedef enum{occupied, reserved, free} Status;
typedef enum{} PlaneStatus;

class Berth{
	private:
		Status status;
		
	public:
		Berth(){
			status = free;
		}
		
		bool reserve(void){
			if (status == free){
				status = reserved;
				return true;
			}
			return false;
		}
		
		bool occupy(void){
			if (status == reserved){
				status = occupied;
				return true;
			}
			return false;
		}
		
		void free(void){
			status = free;
		}
		
		bool isFree(void){
			return status==free;
		}
}

class Taxiway{
	private:
		Status status;
		
	public:
		Berth(){
			status = free;
		}
		
		bool occupy(void){
			if (status == free){
				status = occupied;
				return true;
			}
			return false;
		}
		
		void free(void){
			status = free;
		}
		
		bool isFree(void){
			return status==free;
		}
}

#endif
