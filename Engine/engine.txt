finally now the sql tree which we made now its time for the execution okay so see we like have the tree we now need to
 make the code gen which calls out small small functions which are known as bytecodes 



-------put this when in the fucntions are made okay __-------------------------
maybe before jumping to it i thought adding some of research i did so maybe thaught to put it in see like the database
 file and the normal files like csv files are different ofc they are ( my stupid ass took a hell lot of time to figure 
 this out haha ) and see we have the thing where like to put the cursor somewhere see we dont have the array here so that 
 we can put anywhere we just have the bytes of it so liek each and every word in the string count as a byte so then as per
  it we like position our cursor there and same as for loop

-------------------------------------------------------------------------------





see i am making this thing bottom up method so the very first thing which i did was to ofc go through the sql lite 
documentation read about the bytecode so see these functions are like 
function-name  register-1 register-2 register-3 register-4  
first 3 are integers but the register 4 is kept like for a backup suppose some string appear or some null occur then 
it needs to be taken care of 

then we have the registers see its like a playground all the operations occur here all the data is stored here think 
like everything which needs to be occuring happens here 
it have like length for the blob ( url for the images ) or string 
and space for the integers / float / strings 
and type for it what is the type of data in the thing 

so the thing is each and every of these pointers are used differently every single time so yeah had to document it 

begin_op = nothing meaningful 

goto_op = (p2 = which step ) go to any step there in the code or the list 

halt = stop or return nothing useful 

integer_op / real_op = (p1 = which number , p2 = where to add  ) integer or the float 

blob_op = ( p2 = where to add && p4 = the url && p1 = lenght )  the url for images or some random ass strings 

string_op = ( p2 = where to add && p4 = the string && p1 = lenght )  the strings 


copy_op  = ( p2 = where to copy && p1 = what to copy ) copy the whole register and then put 

move_op = ( p2  = where to move && p1  = what to move and delete ) the p2 copies the address of the p1's register and 
then p1 free itself 

add_op/subs_op/divide_op/mul_op = ( p1 = first operand  && p2 = second operand && p3 where to add the result of these )
 so here if one of 
them is like integer and one as a float then we convert the integer to the float and then do the operation which is there
to and out result type is the same way as well 


gt/eq/lt/ge/le = ( p1 = right side candidate && p2 = if condition correct where to go && p3 = left side candidate &&
 p4 = for getting the type of equations for the string operations for example binary , nocase etc etc ) yeah the same
  case here as well if integer and float we convert the integer to float and then compute whatever there is to 


cursor operations :- 
    structure of the btrees :- okay here so we have kept the thing as first eh start_root_num the starting page num and then the 
    pagenum  of the thing and then the row num which row we are on the datatype fo the thing for the leafs or not we have the 
    mode and the depth for the stack and then we have the stack ( stacks data stucture si like the pagenum of the thing adn the 
    cell index of the thing in the array ) and then we have the have tyhe database file for cehcking fi the colums which we want
     are present or not and then we have the bools for the start and the end if the array is starting ro ending some where we 
     can just apply in here 

    open_read_op and open_write_op  and close cursror :- here see we like make a new stucutre which stores all the infornmation 
    about the cursor which is there and as our thing is the btree we need to work on so it contains that stuff same things 2 
    types there are read and the write ones that way 1. table looks for which so the tuple it is for which we have the a special
    file db which is made and there we look for the things then we have te pagenum while paging we store need to store the page
    num of the current node and the start root num the root from where we start the tree so yeah and similarly the clsoe 
    cursor op we just free out the things which we store in our cursor all the info we have kept only p2 register is used which
    cursor to do things so it is used it for that one 

    next_cursor and prev_cursor :- so see we keep the reocord of all the nodes or all the trees which are there in the thing in
     a stack so that we can have the track of all the nodes through which we are going so like see if the in a perticular node
      if the space ends we need to go to another end of the parent node if there space is present so so we just check if the 
      the parent node in the array is less than the capacity of its holding why so see its like we are travesring backwards 
      right so if the space was available in the thing so it would have gone so we keep on searching for the current place 
      should be less than the total capacity and then we keep on adding the same things in the stack again and again as well 
      yeah thats the logic similar kind of logic for the prev cursor as well 
    
    rewind_cursor and cursor_end :- here the thing is we are just going to end or the first place of the array in the tree so 
    its like that simple we just go till we dont hit the leaf simple 
    
    seek operations :_ this is the function which like looks for the value of the node which is greater than the registers 
    value in the register the address to that register is given in the p1 so what we do is see when we reach the children we 
    like start out binary search on all the children present inside the child's parent which we reach earleir and then we first
    do the binary search on it and campare them if we found well and good if not we just need to jump to the next parent so 
    see our struct stores the total number of terms so we just need to take a vairlable which adds all the children on which
    we are applyng binary search and then move to the next one the same algorithm we used on th cursor next just with a tiwst
    see our thing is the camparision starts fronm very start we keep on checking the highest number which can be present see
    this thing is avaible in the header of the tree so its easier that way you know and then we kind of get to know exactly
    where all the to go which direction to pick optimised effiecient and bs actually fruitfull else the bs works like a
    stupid linear search only so we go the bs simple its the same we have the pointer to the childrens addrrss and then
    we just do normal bs on it and also have few additional functions which take the position data fromn the file and 
    then take it for camparision 


aggregate functions :- 
    info about the struct here so see we have the registers directly for the min and the max and the total for the arithmatic
     operations an the have value is present here for the camparision in the min and max and then we have the count it tracks 
     all the coutns of the thing used in avg and count and then the concat string its like if we have the operation to concat 
     the string so we use it 
    
    aggregate step = same thing here as well we keep a track of the aggregarte function we make a struct of the same and then 
    as per the operation is there we keep on updating it so like if the register number stored in the p2 register is the number
     from which we keep on storing 
    
    aggregate final = here whatever we have been storing all the things swe now transfer them into the register number p3 
    register and store it and use it for further usecase 

sort :- 
    the structure used for the thing is like we ave the row_count to see where we are and then the capacity of the thing is 
    check and the keycols is how many of the things need to be sorted and then the cols to look is for the which of the columns 
    needs to be on basis of which we need to sort and then we have the keyinfo in it which is like we need to asc desc or the 
    string operations commands are given , and then comming to the main thing the thing where we store the data of the thing 
    so one is the the normal where we store the blob ( its like we during the make record time all the info about thet register
     is stored in the a blob and then used ) okay so this is what we have then len of the deciding factor's lenght  and then 
     the key the column's value on which we want to sort and then the keytype like the data type thing 
    
    see in the orderby functions we need to sort the things with respect to something right so we need to store all the things 
    in the spcial sturct and then we operate on it okay so in the sorter_open we make the struct and then we store the which
     columns to look for the sorting which is given in the p2 register and then we also store the keyinfo in the p4 register 
     it contains thsoe stuff only the desc or asc or the string camparision stuff only we also have a different struct for it 
     as well 
    
    in the next function which is the sorterinsert we just a enter the number or update the parameters in the sort structure 
    like increating the capacity if the count and the capacity is the same and then reallocate the term to the length of the 
    term we are going to add and then add it in the thing so yeah liek that 
    
    sorter_sort this one is classic we just sort it now directly what we have in the struct so our work is usally done by the 
    qsort here see its a function in the linux what it does is just take up all struct which needs to be camapred how many of 
    the terms need to be operated size of the campred strucr and then the function which decides we need to switch the things 
    or not and then as here we also have the some instructions on basis we need to like sort so we also have that one attribute 
    as well for the thing okay so campare function is similar to the ge_op so yeah its pretty similar to it  we also have a 
    different function which like takes the data on which we are going to camapre thing the deciding factor number so we like 
    go to the thing so see its like each of the row is stored in the blob here lets assue like 23|varad|21 here the | is not 
    there i just gave for refernce so here the in the blob its stored liek the datatype and the direct data and if the type is 
    the string then the lenght of the string is been also given so we take these info make our position go there in the blob 
    take the data take the lenght of the thign and the datatype of the thing is also captured from here only 
