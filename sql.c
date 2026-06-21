#define _DEFAULT_SOURCE
#define _BSD_SOURCE
#define _GNU_SOURCE
#include<stdio.h>
#include<unistd.h> 
#include<termios.h>
#include<ctype.h>
#include<stdlib.h>
#include<string.h>
#include<errno.h>
#include<sys/ioctl.h> 
#include<sys/types.h>
#include<time.h>
#include <stdarg.h>
#include <stdbool.h>
#include <fcntl.h>
#define ctrl(k) ((k) & 0x1f) 
#define version "0.0.1"
#define tab_spaces 8
#define quit 1

typedef struct row_input{ 
	int size ; 
	char *data ; 
	char *render  ; 
	int render_size ; 
	bool query ; 
	bool comment ; 
	int comment_close_col ;
	unsigned char *hl  ; 
} row_input ; 

void status_msg_input(const char* msg, ...);
void screen_ready(void);
int  raw_key_press(void);
char *query_data_recovery(void);
 
struct editor_global { 
	int cursor_rows ; 
	int cursor_cols ; 
	int rows  ; 
	int cols ; 
      int row_offset ; 
	int col_offset ; 
	row_input *ri ;
	int row_length ; 
	int changes ; 
	struct termios original  ; 
      int render_cols ; 
	char *filename ; 
	char status_messege[80] ; 
	time_t messege_time ; 
	int comment_start  ; 
	int query_lines ; 
	int *col_max_sizes ; 
} ;

struct proper_data_we_need { 
	char **query  ; 
	char ***data ; 
} ;

struct proper_data_we_need proper_data ; 
struct editor_global  edit ; 

struct dynamic_buffer{
 	char *data ; 
	int size ; 

} ;
char * temp = NULL  ; 

int first = 0 ; 

enum settings_keys {
	Backspace = 127 , 
    Arrow_left = 1000 ,
    Arrow_right ,
    Arrow_up ,
    Arrow_down ,  
    Page_up , 
    Page_down , 
    Home_key , 
    End_key  , 
    delete 
} ;

enum hl{
	hl_normal = 0 ,
	hl_number , 
	hl_search  , 
	hl_comment , 
	hl_syntax
} ; 


#define dynamic_buffer_starter { NULL , 0 } 




char*saving_name(char *name , void (*func)(char *  , int  ) ){
	size_t max  = 128  ; 
		int len = 0 ; 
	char * buf = malloc( max)  ; 

	buf[0] = '\0' ; 
	while(1) {
		status_msg_input(name , buf) ; 
		screen_ready() ; 
		int c = raw_key_press() ; 
		if ( c == delete || c == Backspace || c == ctrl('h')){
			if ( len != 0 ){
				len = len -1 ; 
				buf[len] = '\0' ; 
			}
		}
		else if ( c == '\r' ){
			status_msg_input(" ") ; 
			if ( func != NULL) {
				func(buf , c ) ; 
			}
			return buf ; 
		}
		else if ( c == '\x1b'){
			status_msg_input("The saving is cancel ") ; 
			if ( func != NULL) {
				func(buf , c ) ; 
			}
			free(buf) ; 
			return NULL ; 
		}
		else { 
			if ( !iscntrl(c) && c < 128 ){
				if ( len == max -1 ){ 
					max  = max *2 ; 
					buf  = realloc(buf ,max ) ; 
				}
				buf[len] = c  ; 
				len++ ; 
				buf[len] = '\0' ; 
			}
			if ( func != NULL) {
				func(buf , c ) ; 
			}
		}
	}
}




int render_to_cols(row_input *row  , int pos ){
	int curent_pos =  0 ; 
	for ( int i = 0 ; i < row->size ; i++ ){
		if ( row->data[i] == '\t'){
			curent_pos = curent_pos + (tab_spaces  -1 ) - ( curent_pos % tab_spaces ); 
		}
		else{
			curent_pos++ ; 
		}
		if ( curent_pos > pos ){ 
			return i ; 
		}
	}
	return row->size  ; 
}


void dynamic_buffer_append( struct dynamic_buffer *temp  , const char *s , int len  ){ 
    char *need = realloc(temp->data , temp->size+len) ;
     if (need == NULL) {
         return ;  
     } 
     memcpy( &need[temp->size] , s , len ) ; 
     temp->data = need ; 
     temp->size += len ; 
} 



void finder_word(char *ques ,  int pos  ){
  static int last_match = -1;
  static int  status ; 
  static char *status_line  = NULL ; 
  if ( status_line != NULL ){
	memcpy(edit.ri[status].hl , status_line , edit.ri[status].render_size   ) ; 
	free(status_line) ; 
	status_line = NULL ; 
  } 
  static int direction = 1;
	  if (pos == '\r' || pos == '\x1b') {
   		 last_match = -1 ; 
		 direction = 1 ; 
		 return ; 
 	 }
	else if (pos == Arrow_up || pos == Arrow_left ){
		direction = -1 ; 
	}
	else if (pos == Arrow_down || pos == Arrow_right  ){
		direction = 1 ; 
	}
	if ( last_match == -1 ){
		direction = 1 ; 
	}
	int current  = last_match ; 
	for ( int i =  0 ; i < edit.row_length ; i++ ){
		current  = current + direction  ; 
		if ( current == -1 ){
			current = edit.row_length-1 ; 
		} 
		if ( current  == edit.row_length){
			current = 0 ;
		}
		row_input * row  = &edit.ri[current] ; 
		char *found = strstr(row->render , ques) ; 
		if ( found ){
		last_match = current ; 
		edit.cursor_rows = current ; 
		edit.cursor_cols = render_to_cols( row , found - row->render ) ; 
		status = current ; 
		status_line = malloc(row->render_size ) ; 
		memcpy(status_line , row->hl , row->render_size   ) ; 	
		memset(&row->hl[found - row->render ] , hl_search , strlen(ques)  )  ; 
		if ( edit.cursor_rows < edit.row_offset ){
			edit.row_offset = edit.cursor_rows ;
		}
		if ( edit.cursor_rows  >  edit.row_offset + edit.rows ){
		edit.row_offset = edit.cursor_rows ; 
		} 
		break ; 
		}
}
} 


void finder(){
	int prev_cols = edit.cursor_cols ; 
	int prev_rows  = edit.cursor_rows; 
	int prev_colset  = edit.col_offset; 
	int prev_rowset  = edit.row_offset; 
	char *ques = saving_name("escape = cancel and enter = continue , enter your question %s " , finder_word ) ; 
	if ( ques != NULL ){ 
		free(ques) ; 
	}
	else { 
	edit.cursor_cols =  prev_cols  ; 
	edit.cursor_rows =  prev_rows  ; 
	edit.col_offset =  prev_colset  ; 
	edit.row_offset =  prev_rowset ; 
	}
	

}






void status_msg_input (const char* msg , ...  ){ 
    va_list temp   ; 
	va_start(temp  , msg) ; 
	vsnprintf( edit.status_messege , sizeof(edit.status_messege ) , msg , temp) ; 
	va_end(temp) ; 
    edit.messege_time = time(NULL) ; 
}


char *before_saving(int *buflen){
	int len = 0 ; 
	for ( int i = 0 ; i < edit.row_length ; i++ ){ 
			len = len + edit.ri[i].size ; 
	}
	*buflen = len+edit.row_length ; 
	char *buf  = malloc(len+edit.row_length)  ; 
	char *p = buf ; 
	for ( int i = 0 ; i < edit.row_length  ; i++ ){
		if ( edit.ri[i].query == false){
		memcpy( p , edit.ri[i].data , edit.ri[i].size) ; 
		p = p + edit.ri[i].size ; 
		*p = '\n' ; 
		p++ ; 
		}
	}

   return buf ; 
}

void saving(){
	if (edit.filename == NULL){
		edit.filename = saving_name("Enter file name %s" , NULL) ; 
	}
	if (edit.filename == NULL){
		status_msg_input("Save cancelled.") ;
		return ;
	}
	int len  ; 
	char *buf = before_saving( &len ) ; 
	int token  = open(edit.filename ,   O_RDWR | O_CREAT , 0644) ; 

	if ( token != -1 ) { 
	if ( ftruncate(token , len ) != -1 ) {   
	if ( write( token , buf  , len ) == len ){ 
		status_msg_input("%d copied to the file " , len) ; 
		edit.changes = 0 ; 
	close(token) ; 
	free(buf) ; 
	return  ; 
	} 
	} 
	close(token) ; 
	}
	status_msg_input("Error file could'nt be saved " ) ; 
	free(buf) ; 

} 

void free_dynamic_buffer ( struct dynamic_buffer *temp){
      free(temp->data)  ; 
}

int seperator(int c ){
	return isspace(c) || c == '\0' || strchr(",.()+-/*=~%<>[];", c) != NULL ; 
}




char *SQLITE_HL_keywords[] = {
  "CREATE", "TABLE", "VIEW", "INDEX", "TRIGGER", "VIRTUAL", "DROP", "ALTER",
"ADD", "COLUMN", "RENAME", "ATTACH", "DETACH", "DATABASE",
"SELECT", "INSERT", "UPDATE", "DELETE", "REPLACE", "INTO", "VALUES", "SET",
"FROM", "WHERE", "RETURNING", "UPSERT",
"JOIN", "INNER", "LEFT", "RIGHT", "FULL", "OUTER", "CROSS", "NATURAL", "ON",
"USING", "GROUP", "BY", "HAVING", "ORDER", "ASC", "DESC", "LIMIT", "OFFSET",
"UNION", "INTERSECT", "EXCEPT", "ALL", "DISTINCT", "WITH", "RECURSIVE", "AS",
"WINDOW", "OVER", "PARTITION", "ROWS", "RANGE", "GROUPS", "BETWEEN",
"UNBOUNDED", "CURRENT", "ROW", "PRECEDING", "FOLLOWING",
"PRIMARY", "KEY", "FOREIGN", "REFERENCES", "UNIQUE", "NOT", "NULL", "DEFAULT",
"CHECK", "CONSTRAINT", "WITHOUT", "ROWID", "STRICT", "AUTOINCREMENT",
"CONFLICT", "ROLLBACK", "ABORT", "FAIL", "IGNORE", "CASCADE", "RESTRICT",
"NO", "ACTION", "DEFERRABLE", "DEFERRED", "INITIALLY", "IMMEDIATE",
"BEGIN", "COMMIT", "END", "TRANSACTION", "SAVEPOINT", "RELEASE",
"EXCLUSIVE", "CONCURRENT",
"AND", "OR", "IN", "LIKE", "GLOB", "REGEXP", "MATCH", "IS", "ISNULL",
"NOTNULL", "EXISTS", "CASE", "WHEN", "THEN", "ELSE", "CAST", "COLLATE",
"RAISE", "INDEXED", "UNINDEXED",
"PRAGMA", "VACUUM", "ANALYZE", "REINDEX", "EXPLAIN", "QUERY", "PLAN",
"TEMP", "TEMPORARY", "IF", "EACH", "FOR", "OF", "NEW", "OLD",
"BEFORE", "AFTER", "INSTEAD" , 
"TRUE", "FALSE", "CURRENT_TIME", "CURRENT_DATE", "CURRENT_TIMESTAMP",
"INTEGER", "INT", "REAL", "TEXT", "BLOB", "NUMERIC", "BOOLEAN",
"DATE", "DATETIME", "FLOAT", "DOUBLE", "CHAR", "VARCHAR", "CLOB", NULL 
};

char *C_HL_keywords[] = {
  "int", "char", "short", "long", "float", "double", "void",
  "signed", "unsigned",
  "const", "volatile", "restrict", "_Atomic",
  "auto", "static", "extern", "register",
  "if", "else", "switch", "case", "default",
  "for", "while", "do",
  "break", "continue", "return", "goto",
  "struct", "union", "enum", "typedef",
  "sizeof", "alignof", "alignas",
  "_Bool", "_Complex", "_Imaginary",
  "_Static_assert", "_Noreturn", "_Generic",
  "_Thread_local",
  "inline", "__inline__",
  "__asm__", "asm", "__volatile__",
  "__attribute__", "__typeof__",
  "__restrict__", "__inline",
  "NULL", "true", "false",

  NULL
};

bool if_syntax( char* word ){
	for ( int i = 0 ; SQLITE_HL_keywords[i] != NULL ; i++  ){
	if (strcmp( word , SQLITE_HL_keywords[i]  ) == 0 ){
		return true ; 
	}  ; 
	}	
	return false ; 
}



void color(row_input * row){
	row->hl = realloc(row->hl ,row->render_size ) ; 
	memset(row->hl , hl_normal , row->render_size ) ; 
	int prev_col = -1  ; 
	bool check = true  ; 
	bool comment = false ; 
	int i = 0 ; 
	int k = 0 ; 
	char *buf  = NULL ;
	int col = 0 ;  
	while (i < row->render_size ){
		if(i >= 1 ){ 
			check = seperator(row->render[i-1]) ; 
		}
		else { 
			check = true ; 
		}
		if ( i+1 < row->render_size && row->render[i] == '/' && row->render[i+1] == '/' ) {
			comment = true  ; 
		}
		if (comment) {                    
            row->hl[i] = hl_comment ;
            i++ ;
            continue ;
        }

	

		if ( isdigit(row->render[i] ) && (prev_col == hl_number || check == true ) || (row->render[i] == '.' && prev_col == hl_number )) {
			row->hl[i] = hl_number ; 
			prev_col = hl_number  ;
			check = false ; 
		}
		else { 
		if ( seperator(row->render[i]) ){
			if ( buf != NULL ){ 
				if ( if_syntax( buf )){ 
					int mon = col ; 
					while (mon < i ){
						row->hl[mon] = hl_syntax ; 	
						mon++ ; 	
					}
				}
			free(buf) ; 
			buf = NULL ; 
			}

			k = 0 ; 
			col = i+1   ; 
		}
		else { 
		buf = realloc(buf ,k+2 ) ; 
		buf[k++] = row->render[i] ; 
		buf[k] = '\0' ; 
	
		}
		prev_col = hl_normal  ; 
	}
		i++ ; 
}

	if ( buf != NULL ){
	if ( if_syntax( buf )){ 
		int mon = col ; 
		while (mon < i ){
			row->hl[mon] = hl_syntax ; 	
			mon++ ; 	
		}
	}
	free(buf) ; 
}
}


int decide_color(int hl){
	switch( hl ){ 
		case hl_comment:
			return 31 ; 
	  case hl_number: 
	  	return 32 ; 
		case hl_search :
		  return  34 ; 
	  case hl_normal: 
	  	return 37 ; 
	  case hl_syntax : 
	     return 35 ; 
	}
	return 0 ; 
}



void render_input (row_input *row ) { 
	int tabs  = 0 ; 
	row->render_size  = 0 ;
	for ( int i = 0 ; i < row->size ; i++ ) { 
		if ( row->data[i] == '\t' ) { 
			tabs = tabs + 1 ; 
		} 
	} 
	free ( row->render) ; 
	row->render = malloc( row->size + ( tabs*( tab_spaces -1  )  + 1  ) ) ; 

	int k = 0 ; 
	for ( int i = 0 ; i < row->size ; i++ ) { 
		if ( row->data[i] != '\t') { 
			row->render[k] = row->data[i] ; 
		      k = k + 1 ; 
		} 
		else { 
		   row->render[k] = ' '  ;
			k = k + 1 ;  
			while(k % tab_spaces != 0  )  { 
				row->render[k] = ' '  ; 
		      	k = k + 1 ; 
			} 
	} 
    } 
	  row->render[k] = '\0' ; 
	row->render_size = k ; 
	color(row) ; 
	} 



	       


	void die(const char *s) { 
   write(STDOUT_FILENO , "\x1b[2J" , 4 ) ; 
   write(STDOUT_FILENO , "\x1b[H" , 3 ) ; 
   perror( s ) ; 
   exit(1) ; 
} 
 

 
void append_lines( char *line , int pos  , size_t len) { 
	if ( pos < 0 || pos > edit.row_length){
		return ; 
	}
    edit.ri = realloc( edit.ri , sizeof(row_input)*(edit.row_length+1) )  ;  
	memmove(&edit.ri[pos + 1] , &edit.ri[pos] , sizeof(row_input)*(edit.row_length -pos  )) ; 
    edit.ri[pos].size = len ; 
    edit.ri[pos].data = malloc( len+1 ) ;  
    memcpy(edit.ri[pos].data , line , len) ; 
    edit.ri[pos].data[len] = '\0' ; 
    edit.ri[pos].render = NULL ; 
    edit.ri[pos].render_size = 0 ; 
	edit.ri[pos].hl = NULL ; 
	edit.ri[pos].query = false ; 
    render_input(&edit.ri[pos]) ; 
    edit.row_length++   ; 
	edit.changes++ ; 
}  

void insert_new_lines(){
	bool was_query = edit.ri[edit.cursor_rows].query ;
	if (edit.cursor_cols == 0 ){
		append_lines( "" , edit.cursor_rows  ,  0)  ; 
	}
	else{ 
		row_input *row = &edit.ri[edit.cursor_rows] ; 
		append_lines(&row->data[edit.cursor_cols] , edit.cursor_rows + 1  , row->size - edit.cursor_cols) ; 
		row = &edit.ri[edit.cursor_rows]  ; 
		row->size = edit.cursor_cols ; 
		row->data[row->size] = '\0' ; 
		render_input(row) ; 
	}
   if ( was_query ){            
        edit.query_lines++ ; 
        edit.ri[edit.cursor_rows + 1].query = true ; 
    }
	edit.cursor_rows++ ; 
	edit.cursor_cols = 0 ; 
}




void text_in_input_buffer(char *file){ 
    FILE *fp  = fopen(file , "r") ;
	edit.changes = 0 ; 
    edit.filename = strdup(file) ; 
    if (!fp) {									
      die("fopen") ; 
    }
	edit.row_length = 0 ;
    char *line  = NULL ; 
    size_t mem = 0  ; 
    ssize_t len  ; 
    while ( ( len =  getline(&line , &mem , fp  ) )  != -1  ) { 
    while( len > 0 && (  ( line[len-1] == '\n' ) ||  ( line[len-1] == '\r' ) ) )  {
	    len-- ; 	
	} 
    append_lines( line  , edit.row_length , len )  ; 
   } 
   free( line) ; 
   fclose( fp ) ; 
    for (int i = 0; i < edit.row_length; i++) {
        edit.ri[i].query = false;
    }
	edit.ri[0].query = true;
   first = 1 ; 

} 
void insert_char( row_input *line ,  int pos ,  int c ){ 
	if ( pos < 0 || pos > line->size ){ 
		pos  = line->size ; 
	}
	line->data = realloc( line->data , line->size + 2 ) ; 
    memmove( &line->data[pos+ 1 ] , &line->data[pos] ,  line->size - pos + 1 ) ; 
	line->size++ ; 
	line->data[pos] = c ; 
	render_input(line)  ; 
	edit.changes++ ; 
}





void excel_like(){
    char ***temp = proper_data.data ;
	edit.col_max_sizes = NULL ; 
	free(edit.col_max_sizes) ; 

	if ( temp == NULL ){
		return ; 
	}
	int cols = 0 ; 
	if ( temp[0] != NULL ){
	for ( int i = 0 ; temp[0][i] != NULL ; i++ ){
			cols++ ; 
	}
}
edit.col_max_sizes  = malloc(cols) ; 
	int *max_size = calloc(cols , sizeof(int)) ; 
	for ( int i = 0 ; temp[i] != NULL ; i++ ){
		for ( int j = 0 ; j < cols && temp[i][j] ; j++ ){
				if ( strlen(temp[i][j]) > max_size[j] ){
					max_size[j] = strlen(temp[i][j]) ; 
					edit.col_max_sizes[j] = max_size[j] ; 
				} 
		}
	}
	for ( int i = 0 ; temp[i] != NULL ; i++ ){
		int row  = i + edit.row_offset ; 
		if ( row > edit.row_length ){
			break ; 
		}
		int total = 0 ;
		for ( int j = 0 ; j < cols && temp[i][j] != NULL ; j++ ){
			total += max_size[j] + 3 ;
		}
		char *buf = malloc( total + 1 ) ;
		int m = 0 ; 
		for ( int j = 0 ; j < cols && temp[i][j] != NULL ; j++ ){
			memcpy(&buf[m] , temp[i][j] , strlen(temp[i][j]) ) ; 
			m = m + strlen(temp[i][j])  ; 
			int leftout = max_size[j] - strlen(temp[i][j]) + 1 ; 
			memset( &buf[m] , ' ' ,  leftout  ) ; 
			m = m + leftout ; 
			memset( &buf[m] , ',' ,  1  ) ; 
			m = m + 1  ; 
		}
	        buf[m] = '\0' ;	
			row_input * line = &edit.ri[i]  ; 
			free(line->data) ; 
			line->data = buf ; 
			line->size = m  ; 
			edit.changes++ ; 
	}
	free(max_size) ; 
	for ( int j = 0 ; j < edit.row_length ; j++ ){
        render_input(&edit.ri[j]) ;
    }

}





void disable_raw_mode(){
	if (tcsetattr(STDIN_FILENO, TCSAFLUSH, &edit.original) == -1){
  	  die("tcsetattr");
	}
}


void rawmode(){
    if (tcgetattr(STDIN_FILENO, &edit.original) == -1){
       die("tcgetattr");
    } 
    struct termios temp = edit.original ; 
    temp.c_iflag &= ~(IXON | ICRNL ) ; 
    temp.c_oflag &= ~(OPOST ) ; 
    temp.c_lflag &= ~(IEXTEN|ECHO|ICANON|ISIG ) ; 
    temp.c_cc[VMIN] = 0 ; 
    temp.c_cc[VTIME] = 1 ; 
    if (tcsetattr(STDIN_FILENO, TCSAFLUSH , &temp) == -1){
       die("tcsetattr");
    } 
    if (atexit(disable_raw_mode) != 0 ){
       die("atexit");
    } 
}

int raw_key_press(){
     int temp ; 
	char c = '\0' ; 

     while((temp = read(STDIN_FILENO, &c, 1)) != 1 )   {
	if (temp == -1 && errno != EAGAIN){
       die("read");
    } 
    }

    first = 1 ; 

     if ( c == '\x1b') { 
		char buf[3] ; 
	   if ( read(STDIN_FILENO , &buf[0] , 1) != 1) { 
		return '\x1b' ; 
	      } 
	   if ( read(STDIN_FILENO , &buf[1] , 1) != 1) { 
		return '\x1b' ; 
	     } 
	   if ( buf[0] == '[' ) { 
	       if ( buf[1] >= '0' && buf[1] <= '9' ) { 
		   if ( read(STDIN_FILENO , &buf[2] , 1) != 1) { 
		      return '\x1b' ; 
	           } 
		   if ( buf[2] == '~') { 
 		      switch( buf[1] ) { 
			case '1' : return Home_key;
           	       case '4' : return End_key;
			case '5' : return Page_up ; 
			case '6' : return Page_down ; 	
			case '7' : return Home_key;
           	       case '8' : return End_key;
			case '3' : return delete  ; 
                   } 
		   } 
                  }
		else { 
 	          switch ( buf[1] ) {
	        	case 'A' : return  Arrow_up ; 
	        	case 'B' : return Arrow_down ; 
		       case 'C' : return  Arrow_right ; 
		       case 'D' : return Arrow_left ; 
			case 'H' : return Home_key;
           	       case 'F' : return End_key;
		    }
		}
	       } 
		if ( buf[0] == 'O') { 
		  switch ( buf[1] ) {
			case 'H' : return Home_key;
           	       case 'F' : return End_key;

                 } 
		}	
	return '\x1b'  ; 
    }


    
    else { 
	return c ; 
    } 
    

}

int position_as_per_cursor( row_input *row ){ 
	int num  = 0 ; 
	 for ( int i = 0 ; i < edit.cursor_cols ; i++ ) { 
		if ( row->data[i] == '\t' ) { 
			num = num + (tab_spaces  -1 ) - ( num % tab_spaces ); 
		} 
		else { 
			num = num + 1 ; 	
		}
	} 
return num ; 
} 



void cursor_change(int c ){ 
	int prev_col ; 
	switch (c)  {
	  case Arrow_up : 
		if( edit.cursor_rows  != 0 ) { 
			prev_col = position_as_per_cursor(&edit.ri[edit.cursor_rows])  ; 
		   edit.cursor_rows -= 1  ; 
			edit.cursor_cols = render_to_cols(&edit.ri[edit.cursor_rows] , prev_col ) ; 
		} 
		   break ; 

	  case Arrow_down : 
		if (edit.cursor_rows < edit.row_length - 1 ) {
				prev_col = position_as_per_cursor(&edit.ri[edit.cursor_rows])  ; 
						  edit.cursor_rows += 1 ; 
				   edit.cursor_cols = render_to_cols(&edit.ri[edit.cursor_rows] , prev_col ) ; 
		} 
		break ; 


	 case Arrow_left : 
		if ( edit.cursor_cols == 0  ) { 
			if ( edit.cursor_rows != 0 ) { 
			    edit.cursor_rows -= 1 ; 
			    edit.cursor_cols = edit.ri[edit.cursor_rows].size  ; 
			 } 
		} 
		else { 
		   edit.cursor_cols -= 1  ;  
		}
		   break ; 


	case Arrow_right : 
	if ( edit.cursor_rows == edit.query_lines -1 && edit.cursor_cols == edit.ri[edit.cursor_rows].size  ){
		break ; 
	}
		if ( edit.cursor_cols < edit.ri[edit.cursor_rows].size ) { 
			edit.cursor_cols += 1 ; 
		} 

		else if ( edit.cursor_rows < edit.row_length  -1 ) { 
		      edit.cursor_rows += 1 ; 
			edit.cursor_cols = 0 ; 
			} 
			break ; 
  }
		
} 


void free_row(row_input *row){
	free(row->render) ; 
	free(row->data) ; 
	free(row->hl) ; 
}
void del_row(int row ){
	if ( row < 0 ||  row >= edit.row_length) {
		return ; 
	}
	free_row(&edit.ri[row]) ; 
	memmove(&edit.ri[row] , &edit.ri[row+1] , sizeof(row_input) * (edit.row_length - row - 1  ) ) ; 
	edit.row_length--;
    edit.changes++;
}

void append_delete_lines(row_input * row  , char *s , size_t len ){
	row->data  = realloc(row->data , len + row->size + 1 ) ; 
	memcpy(&row->data[row->size] , s , len ) ; 
	row->size += len  ; 
	row->data[row->size] = '\0';
	render_input(row);   
	edit.changes++ ; 
}





void del_char( row_input *line  , int pos ){ 
	if ( pos < 0 || pos > line->size ){ 
		return  ; 
	}
    memmove( &line->data[pos ] , &line->data[pos+1 ] ,  line->size - pos  ) ; 
	line->size-- ; 
	render_input(line)  ; 
	edit.changes++ ; 
}



void insert(int c ) {
	if (edit.cursor_rows == edit.row_length ){ 
         append_lines(  "" , edit.row_length , 0 ) ; 
	}
	int pos  = edit.cursor_cols ; 
	insert_char( &edit.ri[edit.cursor_rows] ,   pos ,   c) ; 
	edit.cursor_cols++ ; 
}

void del() {
	if (edit.cursor_rows == edit.row_length ){ 
         append_lines(  "" , edit.row_length , 0 ) ; 
	}
  	if (edit.cursor_cols == 0 && edit.cursor_rows == 0) {
		return;
	} 
	int pos  = edit.cursor_cols ; 
	row_input *row  = &edit.ri[edit.cursor_rows] ; 
	if ( pos > 0 ){ 
	del_char( &edit.ri[edit.cursor_rows] ,   pos-1  ) ; 
	edit.cursor_cols-- ; 
	} 
	else { 
		edit.cursor_cols = edit.ri[edit.cursor_rows - 1 ].size ; 
		append_delete_lines(&edit.ri[edit.cursor_rows - 1 ] ,row->data , row ->size  ) ; 
		del_row(edit.cursor_rows) ; 
		edit.cursor_rows -= 1 ; 
	}
}



int seperator_new(int c ){
	return  c == '\0' || strchr(",()+-/*=~%<>[];", c) != NULL ; 
}

char ***data_tokenizer(){
	char*** data = malloc( (edit.row_length + 1 ) *(sizeof(char**)) ); 
	int data_pointer = 0 ;
	int i = 0 ; 
	while ( edit.ri[i].query == true){
		i++ ; 
	}
	while ( i < edit.row_length ){
		char te[300] ; 
		int j = 0  ; 
		int m = 0 ; 
		char* temp = edit.ri[i].data ; 
		char** strings = malloc((edit.ri[i].size + 2) * sizeof(char*) );
		int len = edit.ri[i].size  ;
		bool exc = false ; 
		for ( int k = 0 ; k < len ; k++ ){
			if ( exc == false && temp[k] == ','){
				te[j] = '\0' ; 
          		  strings[m] = strdup(te) ; 
				  m++ ; 
			 	 j = 0 ; 
			}
			else if (temp[k] == '"' ){
				if ( exc == true ){
					exc = false ; 
				}
				else { 
					exc = true ; 
				}
				continue ; 
			}
			else { 
				if ( j < 299 ){
				te[j] = temp[k] ; 
           		 j++ ; 
				}
			}
		}
		te[j] = '\0' ; 
		strings[m] = strdup(te) ; 
		m++ ; 
		strings[m] = NULL ; 
		
		data[data_pointer ] = strings ; 
		data_pointer++ ; 
		i++ ; 

	}
	data[data_pointer] = NULL; 
	return data ; 
}


char** tokenizer(){
	char *buf  = query_data_recovery() ; 
int j = 0  ; 
int m = 0 ; 
int len = strlen(buf) ; 
char** temp = malloc(300 * sizeof( char* )); 
char te[300] ; 
for ( int k = 0 ; k < len  ; k++ ){
if (isspace(buf[k])  ) {
			te[j] = '\0' ; 
            temp[m] = strdup(te) ; 
            m++ ; 
            j = 0 ;
			    continue;  
        }
if ( seperator_new(buf[k])){
			te[j] = '\0' ; 
            temp[m] = strdup(te) ; 
            m++ ; 
            j = 0 ; 
			char tem[2] = {buf[k] , '\0'} ; 
            temp[m] = strdup(tem)  ; 
            m++ ; 
        }
else { 
            te[j] = buf[k] ; 
            j++ ; 
        }
    }
te[j] = '\0' ; 
temp[m] = strdup(te)  ; 
m++ ; 
temp[m] = NULL ; 
return temp ; 
}



char *query_data_recovery(){
    int i = 0 ;
    int total = 0 ;
    char *buf = NULL ;
    while(i < edit.query_lines){
        buf = realloc(buf , total + edit.ri[i].size + 2) ;
        memcpy(buf + total , edit.ri[i].data , edit.ri[i].size) ;
        total += edit.ri[i].size ;
        buf[total++] = '\n' ;
        i++ ;
    }
    if(buf) buf[total] = '\0' ;
    return buf ;
}


void popup_tables( int height , int width , char** tables ){
	   WINDOW *popup = newwin(height + 2 , width + 2 , 0, 0);
	   box(popup, 0, 0);
	   for ( int i = 0 ; i < height ; i++ ){
		mvwprintw(popup, i +1 ,  2 , "%s" , tables[i]);
	   }
	  	 wrefresh(popup);
		wgetch(popup);
	  	 delwin(popup);
		refresh();
}

void meta_commnds(char *temp){
	if ( strcmp(temp , ".save" )){
		saving() ;
	}
	else if ( strcmp(temp , ".load")){

	}
	else if ( strcmp(temp , ".tables")){
		char **tables = proper_data[0] ; 
		int i = 0 ; 
		int width = 0 ; 
		for (  i = 0 ; tables[i] != NULL ; i++ ){
			if ( strlen(tables[i]) > width){
				width = strlen(tables[i]) ; 
			}
		}
		popup_tables( i  , width ,tables ) ; 
	}
}

void process_query(){
	char **buf = proper_data.query ;
	for ( int i = 0 ; buf[i] != NULL  ; i++ ){
		if ( buf[i][0] == '.'){
			meta_commnds(buf[i]) ; 
		}
	}
}



void process_raw_key_press(){
    static int  quit_times = quit ; 
	int word  = raw_key_press() ; 
	switch (word) {
		case '\r' : 
		insert_new_lines() ; 	
		break ; 
		case ctrl('f') : 
			finder() ; 
			break ; 
	  case ctrl('q') : 
	    if ( edit.changes > 0 && quit_times > 0  ){
			status_msg_input("The file is changed and not saved press %d times for still quitting without saving " , quit_times ) ; 
			quit_times-- ; 
			return  ; 
		}
 		write(STDOUT_FILENO , "\x1b[2J" , 4 ) ; 
	       write(STDOUT_FILENO , "\x1b[H" , 3 ) ; 
	       exit(0)  ; 
              break ; 
		case ctrl('e'): 
			for ( int i = edit.cursor_rows + 1 ; i < edit.row_length ; i++ ){
				edit.ri[i].query = false ; 
			}
			edit.query_lines = edit.cursor_rows + 1 ; 
			 edit.cursor_rows = edit.cursor_rows + 1  ;
			 edit.cursor_cols = 0 ; 
			status_msg_input("Thq query is under execution") ; 
			 if (proper_data.query != NULL) {
				free(proper_data.query);   
				proper_data.query = NULL;
			}
			if (proper_data.data != NULL) {
				free(proper_data.data);     
				proper_data.data = NULL;
			}
			proper_data.query = tokenizer() ; 	
			proper_data.data = data_tokenizer() ; 
			break ; 
	  case ctrl('w'): 
		saving() ; 
		break ; 
	  case Page_up : 
	  case Page_down :
             if ( word == Page_up ) { 
			if ( edit.row_offset - edit.rows > 0 ) { 
				edit.cursor_rows = edit.row_offset - edit.rows  ; 
			   } 
			else { 
				edit.cursor_rows = 0 ; 
			}
		   } 
		  if (word == Page_down ) { 
			if ( edit.row_offset + edit.rows < edit.row_length ){ 
				edit.cursor_rows = edit.row_offset + edit.rows ; 
		   } 
			else { 
			   edit.cursor_rows = edit.row_length - edit.rows ; 
		 } 
	    	} 
		 
 		int times  = edit.rows ; 


		while(times > 0 ) { 
		  if ( word == Page_up) { 
			cursor_change(Arrow_up) ; 
			times-- ; 
		}
		else if ( word == Page_down) { 
			cursor_change(Arrow_down) ; 
			times-- ; 
		}
	}
	break ; 



	  case End_key : 
		if ( edit.cursor_rows < edit.row_offset + edit.rows ) { 
			edit.cursor_cols = edit.ri[edit.cursor_rows].size ; 
		  } 
			break ; 

	  case Home_key : 
		edit.cursor_cols = 0  ; 
		break ; 

      case Backspace:
      case ctrl('h'):
      case delete:
	      if (word == delete){
			 cursor_change(Arrow_right) ; 
		  }
		  del() ; 
        break;

	  case Arrow_up : 
	  case Arrow_down : 
	  case Arrow_left : 
	  case Arrow_right : 
		 cursor_change(word) ; 
		break ; 
	  case ctrl('l'):
      case '\x1b':
         break;
	  default:
         insert(word);
         break;
	}
	quit_times = quit ;  

} 







void scroll_offset(){
	edit.render_cols = 0 ; 
            
	if ( edit.cursor_rows < edit.rows + edit.row_offset && edit.cursor_rows < edit.row_length ) { 
      edit.render_cols = position_as_per_cursor( &edit.ri[edit.cursor_rows] )  ; 
	} 
		
     if ( edit.cursor_rows <  edit.row_offset) { 
            edit.row_offset  = edit.cursor_rows ; 
      }
      if ( edit.cursor_rows >= edit.row_offset + edit.rows ) { 
		edit.row_offset = edit.cursor_rows - edit.rows + 1 ; 
       } 
      if ( edit.render_cols < edit.col_offset) { 
		edit.col_offset = edit.render_cols ; 
	} 
	if ( edit.render_cols >= edit.cols + edit.col_offset ) { 
		edit.col_offset = edit.render_cols - edit.cols + 1  ; 
	} 
} 



void status_msg(struct dynamic_buffer *temp ) { 
	dynamic_buffer_append(temp, "\x1b[7m" , 4) ; 
	int msglen = 0 ;
	msglen = strlen(edit.status_messege) ; 
	if ( msglen > edit.cols){
		msglen = edit.cols ; 
	}
	int k = 0 ; 
	if (msglen > 0 &&  time(NULL) - edit.messege_time  < 5 ){ 
		dynamic_buffer_append(temp, edit.status_messege , msglen) ; 
		k = 1 ; 
	} 
	int tes = 0  ; 
	if ( k == 1 ) tes = msglen ; 
	for (int i = tes ; i < edit.cols ; i++ ){ 
		dynamic_buffer_append(temp, " " , 1) ; 
	}
	dynamic_buffer_append(temp, "\x1b[m" , 3) ; 
}



void status_line(struct dynamic_buffer *temp ) { 
	dynamic_buffer_append(temp, "\x1b[7m" , 4) ; 
	int len = 0 ; 
	 char file[80] ; 
	char position[80] ; 
	int pos_len = 0 ; 
	len = snprintf( file , sizeof(file)  , "%s - %d - %d - %s " , edit.filename ? edit.filename: "no name" , edit.cursor_rows , edit.cursor_cols  , edit.changes ? "org" : "modified")  ; 
	pos_len = snprintf( position , sizeof(position) , "%d-%d" , edit.cursor_rows + 1  , edit.row_length ) ; 
      if(len > edit.cols) { 
		len = edit.cols ; 	
	} 
	if ( len <= edit.cols ) { 
	dynamic_buffer_append(temp, file , len) ; 
	} 
	int space  = edit.cols - pos_len  - len  ; 
	if ( space < 0 ){ 
		space = 0 ; 
	}
	for (int i = 0 ; i < space  ; i++) { 	
			dynamic_buffer_append(temp ," "  ,  1 ) ; 
		}  
	dynamic_buffer_append(temp, position , pos_len) ; 

	

	dynamic_buffer_append(temp, "\x1b[m" , 3) ; 		

} 






void txt_print(struct dynamic_buffer *temp  ){ 
	char welcome[100] ; 
      for(int i = 0 ; i < edit.rows ; i++){
		 int correct_row = i + edit.row_offset ; 

        if ( correct_row >= edit.row_length) {
		if ( first == 0 ) { 
		if ( i == edit.rows / 2 ) {
            int  welcome_len = snprintf(welcome , sizeof(welcome) , "PALX excel %s", version ) ; 
		if (welcome_len > edit.cols){
			welcome_len = edit.cols ; 
		}
		int extra =  (edit.cols - welcome_len ) /2 ; 
		if (extra) { 
			 dynamic_buffer_append(temp, "~" , 1) ; 
			extra-- ; 
		} 
		while(extra > 0 ) { 
		   dynamic_buffer_append(temp, " " , 1 ) ; 
		   extra-- ; 
		} 
		dynamic_buffer_append(temp, welcome  , welcome_len ) ; 
		}
          else { 
		    dynamic_buffer_append(temp, "~" , 1) ; 
		} 
		}
		else {  
              dynamic_buffer_append(temp, "~" , 1) ; 
			} 
		} 
else { 
	int temp_len = edit.ri[correct_row].render_size - edit.col_offset ; 
	if (temp_len < 0) { 
		temp_len = 0 ; 
	} 
	if (temp_len > edit.cols) { 
		temp_len = edit.cols ; 
	} 
	if ( edit.ri[correct_row].query == true ){
		dynamic_buffer_append(temp, "\x1b[7m" , 4) ;  
	}
	if ( temp_len > 0 && edit.ri[correct_row].render != NULL && edit.ri[correct_row].hl != NULL ){
		char *row = &edit.ri[correct_row].render[edit.col_offset] ; 
		unsigned char *hl = &edit.ri[correct_row].hl[edit.col_offset] ;
		int prev_color = -1 ; 
		for ( int j = 0 ; j < temp_len ; j++ ){ 
		if (hl[j] == hl_normal) {
		if ( prev_color != -1 ){ 
			dynamic_buffer_append(temp, "\x1b[39m" , 5) ; 
			prev_color = -1 ; 
		} 
			dynamic_buffer_append(temp, &row[j] , 1) ; 
		}
		else { 
		int col = decide_color(hl[j]) ; 
		if ( prev_color != col ){
			char buf[100] ;  
			int len = snprintf(buf , sizeof(buf) , "\x1b[%dm" , col) ; 
			dynamic_buffer_append(temp, buf , len) ; 
			prev_color = col ; 
		}
			dynamic_buffer_append(temp, &row[j] , 1) ;					
		}				
		} 
	}
	dynamic_buffer_append(temp, "\x1b[m" , 3) ;
}
dynamic_buffer_append(temp, "\x1b[K" , 3) ; 
dynamic_buffer_append(temp, "\r\n", 2) ;
}
}



void screen_ready(){
        scroll_offset() ; 
        struct  dynamic_buffer temp = dynamic_buffer_starter ; 
	dynamic_buffer_append(&temp, "\x1b[?25l" , 6 ) ; 
	dynamic_buffer_append(&temp, "\x1b[H" , 3) ; 
	txt_print( &temp ) ; 
	status_line(&temp) ; 
	status_msg(&temp) ; 
        char buf[32] ; 
	snprintf(buf , sizeof(buf) , "\x1b[%d;%dH" , (edit.cursor_rows - edit.row_offset )+ 1  ,(edit.render_cols - edit.col_offset )+ 1  ) ; 
       	dynamic_buffer_append(&temp, buf , strlen(buf) ) ; 
	dynamic_buffer_append(&temp, "\x1b[?25h" , 6 ) ; 
        write(STDOUT_FILENO , temp.data , temp.size)  ; 
	free_dynamic_buffer(&temp) ; 
} 


int cursor_position(int *rows, int *cols) {
     char  temp[32];
     unsigned int i  =   0;
     if (write(STDOUT_FILENO, "\x1b[6n", 4) != 4){
        return -1;
     } 

     while (i < sizeof(temp) - 1) {
         if (read(STDIN_FILENO, &temp[i], 1) != 1) break;
   	 if (temp[i] == 'R') break;
   	 i++;
     }

     temp[i] = '\0';
     if (temp[0] != '\x1b' || temp[1] != '[' ) {
        return -1 ; 
      } 
     if(sscanf(&temp[2]  , "%d;%d" , rows , cols ) !=2 ) {
          return -1 ; 
      } 
     return 0;                         
}
	

int get_window_size(int *rows , int *columns){ 
	struct winsize ws ; 
	if(ioctl(STDOUT_FILENO , TIOCGWINSZ , & ws ) == -1 || ws.ws_col  == 0  || ws.ws_row == 0 ) {
		if (write(STDOUT_FILENO , "\x1b[999C\x1b[999B" , 12) != 12){ 
			return -1 ; 
		} 
   		return  cursor_position (rows , columns ) ; 

	}
	else { 
		*columns = ws.ws_col ; 
		*rows = ws.ws_row ; 
       	return 0 ; 
	}
	
} 

void starter(){
      edit.cursor_rows = 0 ; 
      edit.cursor_cols = 0 ;
	edit.row_length = 0 ; 
    edit.ri = calloc(1, sizeof(row_input)) ;  
      edit.row_offset = 0 ; 
	  edit.changes = 0  ; 
	  edit.comment_start = -1 ; 
	edit.col_offset = 0 ; 
	edit.query_lines = 0 ; 
	proper_data.data = NULL ; 
	proper_data.query = NULL ; 

      if(get_window_size(&edit.rows , &edit.cols) == -1 ) { 
		die("get_window_size") ; 
	} 
	edit.status_messege[0] = '\0' ; 
	edit.messege_time = 0 ; 
	edit.rows  = edit.rows - 2  ; 
	edit.ri[0].query = true ; 
    edit.query_lines = 1 ;
	edit.filename = NULL ; 
	    edit.row_length = 1 ; 
}


int main(int argc , char *argv[] ){
    rawmode() ; 
    starter() ;
    if (argc >= 2 ){ 
	 text_in_input_buffer(argv[1]) ; 
	 	proper_data.data = data_tokenizer() ; 
	excel_like() ; 
	} 
	status_msg_input( "ctrl + w for saving the file | ctrl + q for quitting | ctrl + f for finding words ") ; 
    while(1) {
     screen_ready() ; 
    process_raw_key_press() ; 
    }
    return 0 ; 
} 

