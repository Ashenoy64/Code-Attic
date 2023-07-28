#include "queue.h"
#include "dll.h"
#include "music_player.h"
#include <stdio.h>
#include <stdlib.h>

playlist_t* create_playlist() // return a newly created doubly linked list
{
	// DO NOT MODIFY!!!
	playlist_t* playlist = (playlist_t*) malloc(sizeof(playlist_t));
	playlist->list = create_list();
	playlist->num_songs = 0;
	playlist->last_song = NULL;
	return playlist;
}

void delete_playlist(playlist_t* playlist) // delete the playlist
{
	// DO NOT MODIFY!!!
	delete_list(playlist->list);
	free(playlist);
}

music_queue_t* create_music_queue() // return a newly created queue
{
	// DO NOT MODIFY!!!
	return create_queue();
}

void clear_music_queue(music_queue_t* q) // clear the queue q
{	
	// DO NOT MODIFY!!!
	delete_queue(q);
}

void add_song(playlist_t* playlist, int song_id, int where) //  add a song id to the end of the playlist
{
	if(where==-1)
	{
		insert_front(playlist->list,song_id);
		
	}
	else if(where==-2)
	{
		insert_back(playlist->list,song_id);
	}
	else{
		insert_after(playlist->list,song_id,where);
	}
	if(playlist->num_songs==0)
		{
			playlist->num_songs=0;
		}
	playlist->num_songs++;

}

void delete_song(playlist_t* playlist, int song_id) // remove song id from the playlist
{
	// if(song_id==playlist->last_song->data)
	// {
	// 	playlist->last_song=NULL;
	// }
	delete_node(playlist->list,song_id);
	playlist->num_songs--;
	if(playlist->num_songs==0)
	{
		playlist->last_song=NULL;
	}
}

song_t* search_song(playlist_t* playlist, int song_id) //return a pointer to the node where the song id is present in the playlist
{
	return search(playlist->list,song_id);
}
int searched=0;
node_t *previous_song=NULL;
void search_and_play(playlist_t* playlist, int song_id) // play the song with given song_id from the list(no need to bother about the queue. Call to this function should always play the given song and further calls to play_next and play_previous)
{
	node_t* p=search_song(playlist,song_id);
	if(searched==0 && p!=NULL)
	{
		play_song(p->data);
		previous_song=p;
		searched=1;
	}
	else if(p!=NULL) 
	{
		searched=2;
		playlist->last_song=previous_song;
		previous_song=p;
		play_song(p->data);

	}
	else{
		return;
	}
}

void play_next(playlist_t* playlist, music_queue_t* q) //  play the next song in the linked list if the queue is empty. If the queue if not empty, play from the queue
{
	if(q->front==NULL)
	{
		
		if(playlist->list->head==NULL)
		{
			return;
		}
		else if(playlist->last_song!=NULL && searched)
		{	
			searched=0;
			if(previous_song->next==NULL)
			{
				playlist->last_song=playlist->list->head;
			}
			else{
				playlist->last_song=previous_song->next;
			}
			play_song(playlist->last_song->data);
			//playlist->last_song=playlist->last_song->next;
		}
		else if(playlist->last_song!=NULL)
		{
			if(playlist->last_song->next!=NULL)
			{
				
				play_song(playlist->last_song->next->data);
				playlist->last_song=playlist->last_song->next;
				return;
			}
			else{
				;
				play_song(playlist->list->head->data);
				playlist->last_song=playlist->list->head;
			}
		}
		else//(playlist->last_song==NULL)
		{
			
			playlist->last_song=playlist->list->head;
			play_song(playlist->last_song->data);
			return;
		}


		
	}
	else{
		int data=dequeue(q);
		playlist->last_song=search_song(playlist,data);
		play_song(data);
	}
}

void play_previous(playlist_t* playlist) //  play the previous song from the linked list
{
    if(playlist->list->head==NULL)
	{
		return;
	}
	else if(playlist->last_song!=NULL && searched==1)
	{	
		
		searched=0;
		play_song(playlist->last_song->data);
		playlist->last_song=playlist->last_song->prev;
	}
	else if(playlist->last_song!=NULL)
	{
		if(playlist->last_song->prev!=NULL)
		{
			playlist->last_song=playlist->last_song->prev;
			play_song(playlist->last_song->data);
			return;
		}
		else{
			playlist->last_song=playlist->list->tail;
			play_song(playlist->last_song->data);
		}
	}
	else
	{
		playlist->last_song=playlist->list->tail;
		play_song(playlist->last_song->data);
	}



}

void play_from_queue(music_queue_t* q) //  play a song from the queue
{
	if(q->front==NULL)
	{
		return;
	}
	play_song(dequeue(q));
}

void insert_to_queue(music_queue_t* q, int song_id) // insert a song id to the queue
{
	enqueue(q,song_id);
}


void reverse(playlist_t* playlist) // reverse the order of the songs in the given playlist. (Swap the nodes, not data)
{
	node_t *p = playlist->list->head;
	node_t *temp = NULL;
    while (p != NULL) 
	{
        temp = p->prev;
    	p->prev = p->next;
        p->next = temp;
        p = p->prev;
    }
    if (temp != NULL)
	{
        playlist->list->head = temp->prev;
	}
}


void k_swap(playlist_t* playlist, int k) // swap the node at position i with node at position i+k upto the point where i+k is less than the size of the linked list
{
	int i=0;
	if(k==1)
	{
		song_t *temp=playlist->list->head;
		playlist->list->head=temp->next;
		playlist->list->head->prev=NULL;
		temp->next=NULL;
		playlist->list->tail->next=temp;
		temp->prev=playlist->list->tail;
		playlist->list->tail=temp;
		return;
	}
	for(int i=0;i+k<playlist->num_songs;i++)
	{
		song_t *p,*q;
		song_t *present=playlist->list->head;
		for(int j=0;j<=i+k;j++)
		{
			if(j==i) p=present;
			else if(j==i+k) {
				q=present;break;
			}
			present=present->next;
		}
		song_t *temp1=p->prev;
		song_t *temp2=p->next;
		p->next=q->next;
		if(q->next==NULL) playlist->list->tail=p;
		else q->next->prev=p;
		p->prev=q->prev;
		q->prev->next=p;
		if(temp1==NULL) playlist->list->head=q;
		else temp1->next=q;
		q->prev=temp1;
		q->next=temp2;
		temp2->prev=q;
	}

}






















// void swap(playlist_t *playlist,node_t *x,node_t *y)
// {
// 	if (playlist->list->head == NULL || playlist->list->head->next == NULL|| x == y)
//         return;
 
//     node_t* Node1 = x;
//     node_t* Node2 = y;
 
//     if (Node1 == playlist->list->head)
//         playlist->list->head = Node2;
//     else if (Node2 == playlist->list->head)
//         playlist->list->head= Node1;
//     if (Node1 == playlist->list->tail)
//         playlist->list->tail = Node2;
//     else if (Node2 == playlist->list->tail)
//         playlist->list->tail = Node1;
 
//     node_t* temp;
//     temp = Node1->next;
//     Node1->next = Node2->next;
//     Node2->next = temp;
 
//     if (Node1->next != NULL)
//         Node1->next->prev = Node1;
//     if (Node2->next != NULL)
//         Node2->next->prev = Node2;
 
//     temp = Node1->prev;
//     Node1->prev = Node2->prev;
//     Node2->prev = temp;
 
//     if (Node1->prev != NULL)
//         Node1->prev->next = Node1;
//     if (Node2->prev != NULL)
//         Node2->prev->next = Node2;
// } 
// void k_swap(playlist_t* playlist, int k) // TODO: swap the node at position i with node at position i+k upto the point where i+k is less than the size of the linked list
// {
// 	if((playlist->list->head==NULL)&&(playlist->list->tail==NULL))
// 	{
// 		return ;
// 	}
// 	else if((playlist->list->head)==(playlist->list->tail))
// 	{
// 		return ;
// 	}
// 	int a=0;
// 	node_t *first=playlist->list->head;
// 	node_t *second=first;
// 	node_t *p;
// 	node_t *q;
// 	while(a<k)
// 	{
// 		a++;
// 		first=first->next;
// 	}
// 	while(a<playlist->num_songs)
// 	{
// 		a++;
// 		p=first;
// 		q=second;
// 		first=first->next;
// 		second=second->next;
// 		swap(playlist,p,q);
// 	}
	
// }


// void k_swap(playlist_t* playlist,int k)
// {
// 	node_t **arr=(node_t**)malloc(sizeof(node_t*)*(playlist->num_songs));
// 	int len=playlist->num_songs;
// 	node_t *p=playlist->list->head;
// 	for(int i=0;i<len;i++)
// 	{
// 		arr[i]=p;
// 		p=p->next;
// 	}
// 	for(int i=k-1,j=0;i<len;i++,j++)
// 	{
// 		p=arr[i];
// 		arr[i]=arr[j];
// 		arr[j]=p;
// 	}
// 	for(int i=0;i<(len/2);i++)
// 	{
// 		p=arr[i];
// 		arr[i]=arr[len-1-i];
// 		arr[len-i-1]=p;
// 	}
// 	playlist->list->head=arr[0];
// 	playlist->list->tail=arr[len-1];
// 	playlist->list->head->prev=NULL;
// 	playlist->list->tail->next=NULL;
// 	for(int i=1;i<len-1;i++)
// 	{
// 		arr[i-1]->next=arr[i];
// 		arr[i]->prev=arr[i-1];
// 	}
// 	arr[len-1]->prev=arr[len-2];

// }


void settail(playlist_t *playlist)
{

	node_t* p=playlist->list->head;
	while(p->next!=NULL)
	{
		p=p->next;
	}
	playlist->list->tail=p;
}

void shuffle(playlist_t* playlist, int k) //  perform k_swap and reverse
{
	if(playlist->list->head==NULL || playlist->list->head==playlist->list->tail )
	{
		return;
	}
  	k_swap(playlist,k);
	
	reverse(playlist);
	settail(playlist);
}

song_t* debug(playlist_t* playlist) //  if the given linked list has a cycle, return the start of the cycle, else return null. Check cycles only in forward direction i.e with the next pointer. No need to check for cycles in the backward pointer.
{
	node_t *p=playlist->list->head;
	node_t *q=p;
	while (p!= NULL &&  q != NULL && q->next != NULL) {
            p = p->next;
            q = q->next->next;
            if (p == q)
                break;
        }
	if(p!=q)
	{
		return NULL;
	}
	else{
		p=playlist->list->head;
		while (p!=q) {
            p=p->next;
            q=q->next;
        }
 
        return p;
 	}
	
}

void display_playlist(playlist_t* p) // Displays the playlist
{
	// DO NOT MODIFY!!!
	display_list(p->list);
}

void play_song(int song_id)
{
	// DO NOT MODIFY!!!
	printf("Playing: %d\n", song_id);
}


