The next part in here is the parser see we posted some queries now what to do with it we need to properly stucture  it right so now the thing 
we do is the very first thing to do is we right now just have the normal character floating out we make the strings of them and then store it 
out so that we can figure out what to do next about it the same is need to be done for the data which we have present in the thing we keep it
 make it as a grid so then like if we want to assign something we make it so this is tokenizer '
So see one curcial info is I am making the whole backend for the csv files cause its relatively easier to work with
So probably for the other files I might make a changer of it so yeah its like that 


One issue which was extremely hurting my eyes was about the files we load those stuture dont look good in the a proper structure for the 
thing the lined stuff is needed so yeah I the best thing is to get the data which we go and then scan in the entire column that if which of 
the size is the highest and record that and then add that much of the spaces in the part now it looks easy but trust me it took entire day of 
the efforts for doing it and the reason was I was trying to do like in 1 iteration itself like record the highest one and then add the 
character thing for the spaces and then bring them to one line but then the issue was first we iterate thorugh our row by row so then the 
thing kind of breaks number 2 the first one can be solved but getting to know where exactly to put the space is also a huge problem it always 
gets curropted now matter what and then next one the data in the render is far more different than the one which we get in the grid so then 
the problem is pretty common so then the best thing to do is just record all the highest size of all the terms and then record it in a array 
and then make a string and then add all the spaces and the data which we have with us and then maker it for each of the row and then put the 
string in the row's data and like that the thing gets updated it was just highly painful to make all those segmentation errors and bus errors
 really were a problem .



The next part is about the meta commands there are several meta commands like .help or .save or .load or more like those these are complete 
different than the normal sql queries so we need to make them aligned here or make them separately 
Okay we go on e by one then the first meta command is the tables once we do it we gt all the tables all the headers we see it so now as we 
Excel so showing those was a problem I could have added them to the status messege but its limited cant be shown fully and also I could have
 just highlighted the part but I got to know about a a popup window for the terminal a pop up window appears you can just just show the contents 
over there and then as soon as the key is pressed the window is closed so I am making use of it as it is not curropting any of the data as well
 of ours so yeah 


After the meta commands there comes the assignment stuff like for example A1 = =AA1 like these of A1 = 20 we can generate formulas out of it 
and then update our data from it so a simple version I took just take all the string and then check out one by one how the things are present 
in the string and then operate on it like first check the assigning rows and columns and then look for the goods of them and then also if 
only 1 = is there then its a direct assignment but if there are = = then there is a formula which is to be given to the thing and then that 
formula generated answer is been given then now also one thing is needed to be noted was if the size of the new assignment is more than the
 max size then entire thing needs to be reset and then again the entire of the structure is need to be made the excel like function is needed
 to be called but if the max size is not changing then there is kind of no need then just operating on the one line is enough of the work so
 a new function is made for the same purposes . 
A detailed view about it first of all we need to fetch the coordinates of the grid which we intend to change so simple till we don't hit any
 of the seperator we catch the things and then we push it to a separate function whose only work is to get the string and then give out the 
coordinates simple logic till the character is not number add those numbers and then till the data is number get those and then give out
 those numbers for the checking 
Now if you see there are two types of assignments first is just passing the things maybe string  or maybe just a number so first of all we 
need to check how many of the = are there in between and if they are found more than 2 its a error so we don't move forward with it and and 
if 1 is there then its a general assignment so we then assign whatever is given directly to the first component 

Intresting part starts from here now there are 2 types in here first assigning a grid component itself or perform operations with it generate
 formulas with it and then assign it to the thing so see we have multiple word here see if there are formulas like SUM/AVG then these can just
 be assigned to the numerical data only and if the data is string then its a problem whereas for the strings only formulation possible is concat
for this version maybe in next version definitely  add more and obv if any numbers come when there are already words present then the there is 
data problem so we directly move outside  cause its a problem . Then the course of action goes like if these functions are called we need to 
check the range of it as well so then checking it and then receiving what data is it we do it I made another function which handles this work
 as well . and obv general data or numbers come we store those as well and if the coordinates are given we unpack it and then store it in a 
place same with the separators as well we go on storing all of them and after the string ends we now have all the operators and operands so 
I made a calculator one ( i took the code from the leetcode question basic calculator I solved it earlier so didn't felt like making it again )
 so yeah those functions solve all the numerical data and give us the final string which needs to be assigned to the first grid component and 
same as with the strings a different function although here its just concatenation so yeah not that huge issue 
Also few function I made for making the life easier was a data_int which like converts all the decimal / normal numbers string to numbers and 
give it back and there was one execute commands which like for the functions like sum and those stuff it takes the ranges and then execute and 
give us the computed work 
Also right now its just the made up for single component assigning itself would attempt to make it for full rows as well but later on versions 
( I kinda wanted to focus more on SQL -LITE ) and I just thought adding this one feature would be awesome so yeah I did it ) 

I love to share some of the errors as well I commited as well so the first one was like in the data_int string to the numbers first of all the '.'
 Checking was in the loop where like it was !seperator(buf[I]) which means it was never meant to be true and one issue was if there were some space
 involved in the thing there was no checking for it which was really sucking the entire function as there were no facilities for it and there were 
clear instructions that if some kind of seperator comes in between directly give out error so yeah I faced a ton more of errors cause of it 
Second one was in the woods see the thing was I was just adding up the alphabets but for correct version we need to multiply the previous one with 
26 so that we can get the correct version and the second issue was some errors which I faced in text editors as well see for the getting the x 
coordinate we need to count the columns and for the y coordinate we need to count the rows so its inverse equation kind of stuff and I was 
passing the it wrong way so there were issues with that one as well and trust me this was the huge problem cuase then the entire of the execute
 commands was in problem cause all of these things were inverted 
Comming to the main function of these engine was assign see the first was if the string is empty then entire function would run so first to 
check if its just empty string or is there something in there so yeah adding that one was important 
Now in the between the 2 assigning terms there are = signs so the thing I was doing was I was over complicating it because of which in few 
cases it didn't even worked well its kind of simple enter the thing only if you are space or = and then go on so yeah I simplified it when
 we camera to earlier versions 
Okay comming on a one problem which I am doing every time right now is freeing things earlier to assign the thing so see when we are like 
assign the new values to the grid I was freeing the thing the issue is now we are allocating the data itself and not the address so the heap 
gets curropted and we get segmentation fault and the same problem was in the found == 2 as well so yeah also comming back the found == 1 I 
also added a while loop before going in the function which passes all the spaces in the thing so that we get correct malloc size to our buffer 

Comming to the problems in found == 2 here the issue was see there are three data storages 1 . Operators   2.strings    3.numbers and here the
 thing was I using a same pointer for appending the stuff in strings  and in numbers which was a huge problem if the thing like a column where
 a number is updated or assigned later on and then we try to make the string operations so the we have to take a new pointer i wanted to reuse
 it it got heavy on me haha and then also added few more edge cases like buf[I] != '\0' cause what if there is none its a problem also I added
 the string of the numbers to the data ( string one ) just incase needed 
Similar kind of mistakes were there afterwards as well 

And then the major one see before entering the function itself the problem was 
For eg you wrote A1 == A2 + A3 
Then it was giving out all of them one by one and then calling the function which was causing the problems so then I had to make the entire loop
 changes before it was directly passed through the proper_data.query now it was like edit.ri was been passed for the thing and also checking if 
all of them were space line or not that check is kind of important so yeah it is done as well 

One of minor mistake which caused me problem was there was this dataint thing there the seperator was passed & this was not defined in the seperator
 function so its was trying to find the integer for the & as well so yeah kind of boo boo hey 



okay comming on the main parser of the queries the select commands see its quite straight forward okay first matter of action 

we need to make a tree ast for the all the query we write here so that we can work on it so simply we make a tree with the nested trees children 
and we store all the syntax termms all the words everything in it 


okay lets talk about the nested queries as well see there is possiblity that we have query inside the query so we need to catch it up so simply 
first we need to fetch the end of the row and the end of the column which is whereever the bracket fulfils the criteria till there we add the things
 and then directly put the nested loop for the select queries 
now see there aare two things which can happen once the ( comes first the if the next term is select we go for recursion but if its not then its 
probably a expression or a display of the terms specifically so first we check the priority of the thing if there is presnet its quite clear for 
the expression but if its not we then look for the next term if its the pirority then also we need to go for the expresison i faced a lot of 
issues in here simply cause of the the thing was like the first operand was declared as the leaf and then once the priroity gets true the tree 
was formed with the operand being not present which leads to the not making plus errors as well so yeah it was like a good safe gaurd and if 
none of it is getting true its just a leaf make it a leaf and then move forward now see here we are in the loop for the strcmp(buf[i][j] , ")") != 0 
so the continue was not at all needed here ( in cases see there is the while loops which like as soon as it ends we need to put the conntinue else we
 would lose that word beacuase of the auto increment in the end ) 




see we often have the expressions used liek a+b AND b*c is not null 
so here a proper tree needs to be formed with the thing so a function is been made for it which picks up these makes the node and then we add the
 operators and the operands in the stack and as per the operators come we look for the prioirty of the operator and as per the priority and the
 number of oeprands needed we pop it out and make a proper tree out of it simple as that and in the end added the flush if the same priotity of the 
operators come then to safegaurd them as well so yeah 
the errors i would love to speak about were 
everywhere the issue of the != and strcmp was there i kind of used it eveerywhere had to change everything and then in the expression more the issues 
were like i like hardcoded the thing like see != are two different seeprators but they are cosdiered as one the same manenr like is null or is not null 
like these how different these are i kind of have kept it like hardcoded if both are the pirority ones then attach it directly which kind of backfired
 let me give you the example like is null is there now here the null is considered as the part of the thing but at the time of liek != null here the 
null is a operand here which was getting kicked of so yeah a problem also the issues came with the number of operands to be taken as well few of the
 functions dont take 2 operands whereas i coded it that way for same to each so it was breaking so had to like complelty define the thing for the 
specific functions giving us what the amount of operands need to be considered and then one more function which i kinda of didnt condidered here was 
the nested queries i didnt really thougth it would be used but yeah it was a bit important so i added that as well a smaller bug as well whatever the 
recursive funcrtion which were called werent check with the null so had to add those functions as well 
and the biggest issue here which caused a hell lot of headache to me like the insanity of headache was the i was adding the select queries in the 
expression tree but instead it was needed to be pushed in the stack which kind of cuased a hell lot of trouble to me it also cuased infinite loop 
as well plus the tree forming was also wrong there plus the last thing of operand needs to made null as like in the stack we only playing with the 
top variable right so the null is very necessary as rthere are condition regarding it so yeah that was it 
it also didnt supported alright the thing here was the it didnt supported function as well had to do that one as well simple logic look out for all 
braces inside of it initialise at 0 and add a bool tag as well for just checking that atleast one of them is present or not so yeah had to add this 
one in the expression and then also after the exprerssion function were called outside the while loop of ( cuase it stops when hitted to the ( 
but when it like in the while loop and then we hit some of the syntax then there was no continue in it as it may go ahead of it so yeah small thing 
cuases huge huge freaking problem . onto the next one see in the function if we need to call the node which needs to be passed was also a big problem 
as well which was caused like if the prev_tree where empty then we needed to liek pass a null tree and then make the tree and join it and if the normal
 cfonditions where there no problem it was the same so yeah 





see we have the functions very comman the sql like count sum avg and so these need to properly insterted in the ast so simply created a function made
 the main node of the thing 2 steps ahead cause we need to avoid the braces and rthen we go inside so simply there can be expressions in the thing or
 there can be nested queries so we need to manage those so yeah added them loop goes on and we get all of them covered so yeah not much to talk about 
this one straightforward as that errors were also like normal " and ' these ones and the null werent taken in the account nothing that much of major 
so yeah 
only one major issue ill tell here was just the see the issue was if the first thing is not the operator with the priority but if the next one is the 
priority is true rthen it needs to be covered inside the operator so we simply needs to push the thing in the expression if the next thing is the
 prioirty thing similar problem was present in here as well for the continue 



okay onto the case expression tree see we have the case syntax for example case '' when '' then '' else '' so simple thing there can be the expression 
or the nested query in the gap only thing is following the syntax correctly so see firsrt case is the boss and then all the when and then reports to case 
but if there is then in the space of the when then it makes a new tree from there and then adds it to the when simple is for that i had to store each of
 the tree inside a array of trees so then keep the track of all the nodes which pass through the when and else and then as soon as we hit the then then
 we just make a new node and then pass the temp to it cause already our temp is set to the when when we enter the thing also the nested case is possible 
so added those things as well 
about the errors i forgoted to added then and then it was more pain to get it covered again and then it hitted infinite loop as well for not adding the 
conitnue in the after the then see you can see how naive the problems or bugs are but trust me when the code is so freaking huge it kills entire eyes to
 patch them up so yeah 






okay finnally on the comp_1 funtion see it was made for the part where ;- select '' from only this much part can be function can be nested loop inside
 can be exprssion those stuff where there and stops at from the from was taken care in the main function so not a huge problem about it few of the problem 
came same i stated it in top majority of them were the same only new one was the * one see if the select * from so if * comes in the thing it instantly
 crashes as it supposes it as a multiplication * and then starts to look for the operands whereas there are none of them only seelct is there and select 
is definately not defined so giving up nothing so yeah it was solved an so one of the most classic mistake or rather the testcase which i didnt really
 took in account was see if we enter the ( thing we need to go till the most endest ) is not achieved i was simply doing it which kind of bad let me 
explain with a example see ( a * ( b+ c ) * d ) so here by the earlier methos we did covered till where to go but the most purest form of the equation 
is needed for the expression now you may think that this could have been never happened if we go in the expression and then 
recursion could have fixed it nope the start and the end are kind of fixed it goes in infinite loop so not relly a good idea for it 


as soon as we cross the from we goes to the next part which is from '' where so in between the nested queries can come the join can come normal expression
 can come so yeah same as the comp_1 i dont wanna convey that much again just the new thing of the join so see let me give you the normal thing see we have
 multiple varianets of the join and then tthere is the on with the join now those are valid for all of the other but not the cross join so the same procedurue
 of the comes the normal again but one thing is different here see we have the union thing for this one if the union comes then in the ast these function 
directly gets attached to the union node else to the normal temp which is going in the thing and then lets move to one of the issue worth telling was the 
on thing see as i mentioned ealrier the on and the cross join is not really possible so see also the issue is on comes in the prioity which we have in the 
expression function so i was taking that condition inside the loop of the expression and as the on wqas in the priority it was breaking everything as the 
operands werent clear either all the logic failed fix was quite simple simply take it out of the loop 1 arrow 2 kills killed entire programe itself haha then 
there was issue in the increment small one not worth honestly so yeah 
