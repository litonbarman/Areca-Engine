#ifndef __ARRECABUFFER_HPP__
#define __ARRECABUFFER_HPP__


#include <iostream>


// completed

namespace Arreca {
	
	template <class Arreca_BufferDataType>
	
	class Arreca_BufferNode {
		public:
		    Arreca_BufferNode* pre;
			Arreca_BufferNode* nxt;
			
			Arreca_BufferDataType data;
			
			Arreca_BufferNode(Arreca_BufferDataType data, Arreca_BufferNode* nxt = 0, Arreca_BufferNode* pre = 0){
				this->data = data;	
				
				this->pre = pre;
				this->nxt = nxt;
			}
		
	};
	
	template <class Arreca_BufferDataType>
	
	class Arreca_BufferQueue {
		private:
		    Arreca_BufferNode<Arreca_BufferDataType>* head;
			Arreca_BufferNode<Arreca_BufferDataType>* tail;
			
			short bufferQueueSize;
		
		public:
		    
			Arreca_BufferQueue(){
				this->head = 0;
				this->tail = 0;
				
				this->bufferQueueSize = 0;
			}
			
			~Arreca_BufferQueue(){
				Arreca_BufferNode<Arreca_BufferDataType>* temp;
				temp = this->head;
				
				while(temp != 0){
					this->head = temp->nxt;
					delete temp;
					temp = this->head;
				}
				
			}
			
			void enqueue(const Arreca_BufferDataType &data){
				this->head = new Arreca::Arreca_BufferNode<Arreca_BufferDataType>(data, this->head);
				
				if(this->bufferQueueSize >= 1){
					this->head->nxt->pre = this->head;
				}
				else{    // when bufferQueueSize == 0
				    this->tail = this->head;
				}
				
				this->bufferQueueSize++;
				
			
			}
			
			Arreca_BufferNode<Arreca_BufferDataType>* dequeue(){
				
				if(this->bufferQueueSize >= 2){
					Arreca_BufferNode<Arreca_BufferDataType>* temp = this->tail;
				    
					this->tail = this->tail->pre;
					this->tail->nxt = 0;
					
					this->bufferQueueSize--;
					
					return temp;
				}
				else{
					return 0;
				}
				
				
			}
			
			
			void display(){
				Arreca_BufferNode<Arreca_BufferDataType>* temp;
				temp = this->head;
				
				while(temp != 0){
					
					std::cout << temp->data.data << " " << temp->data.s << std::endl;
					
					temp = temp->nxt;
				}
				
				std::cout << "\n\nInreverse :-\n";
				
				temp = this->tail;
				
				while(temp != 0){
					std::cout << temp->data.data << " " << temp->data.s << std::endl;
					
					temp = temp->pre;
				}
				
			}
			
	};
	
}




#endif
