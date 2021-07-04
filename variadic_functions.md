# Variadic Functions (My Notes)
'...' in the prototype declaration is known as 'ellipsis' and it indicates that the function can have variable number of arguments.
‘...’ prevents the compiler checking about the number or type of subsequent argument

![image](https://user-images.githubusercontent.com/76621210/124390721-72855f00-dd1f-11eb-9b3a-3bd5c1535c85.png)

### Sequence of Calling the Functions
(1) va_list\
(2) va_start\
(3) va_arg\
(4) va_end

### stdarg.h
The standard header <stdarg.h> contains a set of macro definitions that define how to step through an argument list. 
The implementation of this header will vary from machine to machine, but the interface it presents is uniform.

### va_list ap
The type va_list is used to declare a variable that will refer to each argument in turn (used as a pointer that can be moved through the arguments). 
For example, I named this variable as ap in ft_printf, short for "argument pointer".

### va_start(ap, param)
The macro va_start initializes ap to point to the first unnamed argument. It must be called once before ap is used. 
There must be at least one named argument, the final named argument found is used by va_start to get started.
- va_start returns void, to access the first parameter, we can straight away use the variable name.

### va_arg(ap, type)
Each call of va_arg returns one (current) argument and moves ap to the next argument; 
va_arg requires a data type as parameters to determine what type to return and how big a step to take and move the ap.
- First time calling this function will return the second argument and move the ap from second to third argument, 
because va_start already moves ap from first arg to second arg.
- A type name can be passed as a function argument in this function because va_arg is a macro function 
and the type argument is internally passed to the sizeof operator and the cast operator

### va_end(ap)
va_end does whatever cleanup is necessary. It must be called before the program returns.

### Techniques
While using variadic functions, we need to implement some mechanism to tell the function how many arguments there are. Below are some examples what we can do:\
(i) Pass the number of arguments (count) as the first variable\
(ii) Require the last variable argument to be null, zero or whatever sentinel argument\
(iii) Have the first argument describe what is expected (eg. the printf format string dictates what arguments should follow)

### Common Beginner Mistakes
- The first argument of a variadic function is not necessarily an integer.
- The data types of the arguments followed behind no need to be same, it can be anything and any combinations.
