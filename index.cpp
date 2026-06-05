<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>PHP Reviewer Interactive Quiz</title>
    <!-- Tailwind CSS for modern styling -->
    <script src="https://cdn.jsdelivr.net/npm/@tailwindcss/browser@4"></script>
    <style>
        .correct-flash { background-color: #d1fae5; border-color: #10b981; }
        .incorrect-flash { background-color: #fee2e2; border-color: #ef4444; }
    </style>
</head>
<body class="bg-gray-5xl text-gray-800 font-sans antialiased line-height-7">

    <!-- Header Section -->
    <header class="bg-indigo-900 text-white shadow-md sticky top-0 z-50">
        <div class="max-w-5xl mx-auto px-4 py-4 flex flex-col sm:flex-row justify-between items-center gap-4">
            <div>
                <h1 class="text-xl font-bold tracking-tight">PHP Interactive Reviewer</h1>
                <p class="text-xs text-indigo-200">All 100 Questions Included</p>
            </div>
            <div class="flex items-center gap-4 bg-indigo-950 px-4 py-2 rounded-lg shadow-inner">
                <div class="text-center border-r border-indigo-800 pr-4">
                    <span class="block text-xs uppercase text-indigo-300 font-semibold">Progress</span>
                    <span id="progress-text" class="text-lg font-bold">0 / 100</span>
                </div>
                <div class="text-center">
                    <span class="block text-xs uppercase text-indigo-300 font-semibold">Score</span>
                    <span id="score-text" class="text-lg font-bold text-emerald-400">0</span>
                </div>
            </div>
        </div>
        <!-- Global Progress Bar -->
        <div class="w-full bg-indigo-950 h-2">
            <div id="progress-bar" class="bg-emerald-400 h-2 transition-all duration-300" style="width: 0%"></div>
        </div>
    </header>

    <!-- Main Content Area -->
    <main class="max-w-4xl mx-auto px-4 py-8">
        
        <!-- Welcome & Instruction Card -->
        <div id="welcome-card" class="bg-white rounded-xl shadow-md p-6 mb-8 border border-gray-100">
            <h2 class="text-lg font-bold mb-2 text-indigo-900">Interactive Quiz Mode</h2>
            <p class="text-sm text-gray-600 mb-4">
                Test your knowledge using your exact provided text items. Questions are divided into Multiple Choice, Fill-in-the-Blank, and Matching types. 
                Submit your answer for each question to see immediate feedback.
            </p>
            <div class="flex flex-wrap gap-2">
                <button onclick="scrollToQuestion(1)" class="bg-indigo-600 hover:bg-indigo-700 text-white text-xs font-semibold py-2 px-4 rounded transition cursor-pointer shadow">
                    Start Quiz
                </button>
                <button onclick="showAllAnswers()" class="bg-gray-100 hover:bg-gray-200 text-gray-700 text-xs font-semibold py-2 px-4 rounded transition cursor-pointer">
                    Reveal All Answers
                </button>
            </div>
        </div>

        <!-- Container where all 100 questions are generated -->
        <div id="quiz-container" class="space-y-6"></div>

        <!-- Results Card / Floating Footer Action -->
        <div class="bg-white rounded-xl shadow-lg p-6 mt-8 border border-indigo-100 text-center">
            <h3 class="text-xl font-bold text-indigo-950 mb-2">Quiz Complete?</h3>
            <p class="text-sm text-gray-600 mb-4">Make sure you have answered all 100 items to evaluate your final performance metrics.</p>
            <button onclick="window.scrollTo({top: 0, behavior: 'smooth'})" class="bg-indigo-950 text-white px-6 py-2.5 rounded-lg text-sm font-semibold hover:bg-indigo-900 transition shadow cursor-pointer">
                Back to Top
            </button>
        </div>
    </main>

    <!-- JavaScript Data Structures and Logic Engine -->
    <script>
        // Full array containing all 100 questions parsed directly from the source layout
        const quizData = [
            { id: 1, type: "mcq", q: "A programmer accidentally created an infinite loop. Which issue MOST likely caused it?", options: ["Too many variables", "The condition has arithmetic operators", "Loop condition never becomes false", "Missing HTML tags"], ans: "C" },
            { id: 2, type: "mcq", q: "Complete the nested function call so that it will display Inside.<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>function outer(){\n  function inner(){\n    echo \"Inside\";\n  }\n  ______;\n}\nouter();</pre>", options: ["inner();", "outer();", "function", "echo"], ans: "A" },
            { id: 3, type: "mcq", q: "Analyze the code:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>for ($i=1; $i<=3; $i++){\n  echo $i;\n}</pre>What is the output?", options: ["012", "0123", "12", "123"], ans: "D" },
            { id: 4, type: "mcq", q: "What is the output?<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>echo \"5\" + \"5 students\";</pre>", options: ["10", "55 students", "5", "Error"], ans: "A" },
            { id: 5, type: "mcq", q: "A grading system must store Student Name, Subject, and Grade for hundreds of students. Which structure is MOST appropriate?", options: ["Multiple arrays", "A single multi-dimensional array", "Multiple single-dimensional array", "Multiple variables"], ans: "B" },
            { id: 6, type: "fitb", q: "Complete the function declaration:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>______ greet(){\n  echo \"Hello\";\n}</pre>", ans: "function" },
            { id: 7, type: "mcq", q: "Which software package is MOST suitable for beginners setting up PHP locally?", options: ["XAMPP", "Visual Studio Code", "Composer", "Git"], ans: "A" },
            { id: 8, type: "fitb", q: "Complete the function declaration.<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>______ displayMessage(){\n  echo \"Welcome\";\n}</pre>", ans: "function" },
            { id: 9, type: "mcq", q: "What will be the output?<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$x = 5;\nif($x > 3){\n  if($x < 10){\n    echo \"A\";\n  }else{\n    echo \"B\";\n  }\n}</pre>", options: ["No output", "A", "AB", "B"], ans: "B" },
            { id: 10, type: "mcq", q: "What is the problem in this code?<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>1. $x = 5;\n2. \n3. function test(){\n4.   echo $x;\n5. }\n6. test();</pre>", options: ["Missing echo in line 6", "Undefined variable inside function", "Missing return statement", "No problem"], ans: "B" },
            { id: 11, type: "mcq", q: "What will be the output?<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$x = 0;\nif($x = 1){\n  echo \"YES\";\n}else{\n  echo \"NO\";\n}</pre>", options: ["NO", "YES", "Unknown", "Error"], ans: "B" },
            { id: 12, type: "mcq", q: "Given:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$x = 5 + 3 * 2;</pre>What is the value of $x?", options: ["13", "16", "10", "11"], ans: "D" },
            { id: 13, type: "mcq", q: "Analyze the code:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$numbers = array(10, 20, 30);\necho count($numbers);</pre>What is the output?", options: ["Error", "No output", "2", "3"], ans: "D" },
            { id: 14, type: "mcq", q: "What is wrong with this code?<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>if($x = 5){\n  echo \"True\";\n}</pre>", options: ["No problem in the code", "Condition will always be true", "Undefined variable", "Syntax error"], ans: "B" },
            { id: 15, type: "mcq", q: "A developer wants a webpage to automatically generate customized greetings for each user visiting the site. Which feature of PHP is MOST useful?", options: ["CSS animation", "Browser caching", "Static HTML rendering", "Server-side scripting"], ans: "D" },
            { id: 16, type: "mcq", q: "In PHP, the return datatype of a function MUST be specified when declaring an function.", options: ["True", "False"], ans: "B" },
            { id: 17, type: "mcq", q: "Which scenario BEST demonstrates dynamic web content?", options: ["Fixed image gallery", "Offline text editor", "A printed brochure", "A webpage displaying current weather data from a database"], ans: "D" },
            { id: 18, type: "mcq", q: "PHP is embedded directly within HTML and CANNOT be placed in a separate file.", options: ["True", "False"], ans: "B" },
            { id: 19, type: "mcq", q: "goto helps programs to be more organized and easier to maintain in the long run.", options: ["True", "False"], ans: "B" },
            { id: 20, type: "fitb", q: "Complete the loop so that it will execute 5 times:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>for($i=1; ______)</pre>", ans: "$i<=5; $i++" },
            { id: 21, type: "mcq", q: "What is the output?<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$a = \"10\";\n$b = \"2a\";\necho $a + $b;</pre>", options: ["10", "Error", "12", "102a"], ans: "C" },
            { id: 22, type: "mcq", q: "Which of the choices correctly reflects the output of the statement?<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>echo date(\"m d,Y h:i:A\");</pre>", options: ["06 19, 2026 08:05:57 PM", "6 19, 2026 8:5:57 PM", "Error", "Jun 19, 2026 08:05:57 PM"], ans: "A" },
            { id: 23, type: "fitb", q: "Complete the statement so that it will return the remainder of the two parameters.<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>function multiply($a, $b){\n  ______;\n}</pre>", ans: "return $a % $b" },
            { id: 24, type: "mcq", q: "Which data type is MOST appropriate for storing a student's GPA?", options: ["Integer", "Boolean", "Array", "Float"], ans: "D" },
            { id: 25, type: "fitb", q: "Fill in the missing operator:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$x ______ 5;</pre>to increase $x by 5.", ans: "+=" },
            { id: 26, type: "mcq", q: "Analyze the code:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$i = 1;\nwhile($i <= 3){\n  echo $i;\n}</pre>What is the output?", options: ["12", "123", "Infinite loop", "012"], ans: "C" },
            { id: 27, type: "mcq", q: "Analyze the code:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>function add($a, $b){\n  return $a + $b;\n}\necho add(\"5\", \"3\");</pre>What is the output?", options: ["Error", "8", "53", "Unknown"], ans: "B" },
            { id: 28, type: "mcq", q: "A developer accidentally declared both $Score and $score and the program did not show the output as expected. Why did the program produce unexpected results?", options: ["PHP ignores capitalization", "PHP variables are case-sensitive", "Variables are automatically merged", "PHP converts all variables to lowercase"], ans: "B" },
            { id: 29, type: "fitb", q: "Complete the statement so that it will return the remainder of the two parameters.<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>function multiply($a, $b){\n  ______;\n}</pre>", ans: "return $a % $b" },
            { id: 30, type: "fitb", q: "Complete the logical operator:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>if($x > 0 ______ $y > 0)</pre>Both conditions must be true.", ans: "&&" },
            { id: 31, type: "mcq", q: "A student placed a PHP file on the desktop and attempted to run it directly in the browser. The PHP code appeared as plain text. What is the BEST explanation?", options: ["PHP requires JavaScript to run", "The browser does not support HTML", "PHP scripts require a web server environment and must be placed in a server-specific directory", "The file must be compressed first"], ans: "C" },
            { id: 32, type: "mcq", q: "What is wrong with this code?<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>function calc($a, $b){\n  $a + $b;\n}\necho calc(2,3);</pre>", options: ["Missing echo statement inside the function", "Missing return statement", "Parameters are declared wrong", "Wrong arguments"], ans: "B" },
            { id: 33, type: "fitb", q: "Complete the code so that 'Access Granted' will be displayed if both the conditions are true.<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>if($username == \"admin\" ______ $password == \"1234\"){\n  echo \"Access Granted\";\n}</pre>", ans: "&&" },
            { id: 34, type: "matching", q: "Match the term to its purpose.", terms: ["Browser", "MySQL", "Apache"], options: ["Displays webpages", "Stores data", "Host websites"], ans: ["Displays webpages", "Stores data", "Host websites"] },
            { id: 35, type: "fitb", q: "Complete the function declaration.<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>______ displayMessage(){\n  echo \"Welcome\";\n}</pre>", ans: "function" },
            { id: 36, type: "mcq", q: "Analyze the code:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>function add($a, $b){\n  return \"$a\" + \"$b\";\n}\necho add(5, 3);</pre>What is the output?", options: ["8", "Unknown", "Error", "53"], ans: "A" },
            { id: 37, type: "mcq", q: "A grading system must store Student Name, Subject, and Grade for hundreds of students. Which structure is MOST appropriate?", options: ["Multiple variables", "Multiple arrays", "Multiple single-dimensional array", "A single multi-dimensional array"], ans: "D" },
            { id: 38, type: "mcq", q: "Analyze the code:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$grades = array(\n  array(\"Ana\", 90),\n  array(\"Ben\", 85)\n);\necho $grades[1][0];</pre>What is displayed?", options: ["Ben 90", "Ben"], ans: "B" },
            { id: 39, type: "fitb", q: "Complete the statement to convert \"hello\" to uppercase:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>echo ______,(\"hello\");</pre>", ans: "strtoupper" },
            { id: 40, type: "mcq", q: "Why are variables important in programming?", options: ["They replace servers", "They remove HTML", "They prevent loops", "They store reusable data values"], ans: "D" },
            { id: 41, type: "mcq", q: "A webpage updates product prices automatically from a database every hour. Which concept is MOST related?", options: ["Static rendering", "File compression", "Browser plugins", "Dynamic scripting"], ans: "D" },
            { id: 42, type: "fitb", q: "Evaluate the mathematical expression:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$x = 2;\n$y = 3;\n$z = 4;\necho $x + $y * $z - $y;</pre>What is the output?", ans: "11" },
            { id: 43, type: "fitb", q: "Complete the PHP code block configuration:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>&lt;?php\necho \"Welcome to PHP\";\n______</pre>", ans: "?>" },
            { id: 44, type: "fitb", q: "Complete the loop so that it will execute 5 times:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>for($i=1; ______)</pre>", ans: "$i<=5; $i++" },
            { id: 45, type: "mcq", q: "Multiplication has higher precedence than addition, but lower than division.", options: ["True", "False"], ans: "B" },
            { id: 46, type: "fitb", q: "Complete the function declaration.<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>______ displayMessage(){\n  echo \"Welcome\";\n}</pre>", ans: "function" },
            { id: 47, type: "mcq", q: "Which loop is MOST appropriate when the number of repetitions is known beforehand?", options: ["do..while", "for", "foreach", "while"], ans: "B" },
            { id: 48, type: "mcq", q: "PHP files commonly use the .php extension.", options: ["True", "False"], ans: "A" },
            { id: 49, type: "matching", q: "Arrange the correct flow of web architecture into correct operational sequence numbers.", terms: ["Response is generated in HTML form", "Browser sends request", "Server processes PHP", "Browser receives response"], options: ["1", "2", "3", "4"], ans: ["3", "1", "2", "4"] },
            { id: 50, type: "mcq", q: "include_once() allows duplicate file inclusion.", options: ["True", "False"], ans: "B" },
            { id: 51, type: "fitb", q: "Complete the constant declaration structure configuration:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>______(\"SITE\", \"My Website\");</pre>", ans: "define" },
            { id: 52, type: "mcq", q: "Why is PHP commonly paired with MySQL?", options: ["PHP cannot display HTML", "MySQL compiles PHP code", "MySQL replaces Apache", "PHP is optimized for database interaction"], ans: "D" },
            { id: 53, type: "matching", q: "Arrange the operational logical execution steps in evaluating this expression structure:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$x > 5 && $y < 10</pre>", terms: ["Compare $x > 5", "Compare $y < 10", "Apply logical AND"], options: ["1", "2", "3"], ans: ["1", "2", "3"] },
            { id: 54, type: "mcq", q: "What is the issue with this code?<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>for($i=1; $i>0; $i++){\n  echo $i;\n}</pre>", options: ["Infinite loop", "Nothing", "Syntax error", "Undefined variable"], ans: "A" },
            { id: 55, type: "mcq", q: "A developer wants a webpage to automatically generate customized greetings for each user visiting the site. Which feature of PHP is MOST useful?", options: ["Browser caching", "Server-side scripting", "Static HTML rendering", "CSS animation"], ans: "B" },
            { id: 56, type: "fitb", q: "Complete the code structure configuration layout rules so that 3 will not be displayed in the output loop pipeline layout flow:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>for($i=1; $i<=5; $i++){\n  if($i == 3){\n    ______;\n  }\n  echo $i;\n}</pre>", ans: "continue" },
            { id: 57, type: "fitb", q: "Complete the parameter list initialization format structure rules setup so that each parameter variable will have a default value of 0:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>function add(______){\n  return $a + $b;\n}</pre>", ans: "$a=0, $b=0" },
            { id: 58, type: "fitb", q: "Complete the alternative control flow block conditional structural evaluation template syntax:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>if($age >= 18):\n  echo \"Adult\";\n______;</pre>", ans: "endif" },
            { id: 59, type: "fitb", q: "Complete the loop structural statement to correctly display print numbers configuration from 1 to 5 metrics:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>for($i=1; $i<=5; $i______ ){\n  echo $i;\n}</pre>", ans: "++" },
            { id: 60, type: "fitb", q: "Complete the command expression structural system to view display template output pipeline rules:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>&lt;?php\n______ \"PHP\";\n?&gt;</pre>", ans: "echo" },
            { id: 61, type: "mcq", q: "Type casting permanently changes the original datatype stored in all variables referencing the value.", options: ["True", "False"], ans: "B" },
            { id: 62, type: "mcq", q: "Analyze the conditional block structure execution flow output evaluation:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$x = 5;\nif($x > 3){\n  echo \"A\";\n}else{\n  echo \"B\";\n}</pre>What is displayed?", options: ["No output", "A", "AB", "B"], ans: "B" },
            { id: 63, type: "mcq", q: "What will be the system execution logic output framework evaluation metrics result summary item value?<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$x = 0;\nif($x = 1){\n  echo \"YES\";\n}else{\n  echo \"NO\";\n}</pre>", options: ["NO", "Unknown", "Error", "YES"], ans: "D" },
            { id: 64, type: "mcq", q: "A grading system must store Student Name, Subject, and Grade for hundreds of students. Which structure is MOST appropriate?", options: ["Multiple variables", "Multiple arrays", "Multiple single-dimension array", "A single multi-dimension array"], ans: "D" },
            { id: 65, type: "mcq", q: "Evaluate numerical math expression configuration structure values:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$x = 2;\n$y = 3;\n$z = 4;\necho $x + $y * $z - $y;</pre>What is the output?", options: ["10", "11", "14"], ans: "B" },
            { id: 66, type: "mcq", q: "Analyze the code statement validation configuration loop tracking flow layout:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>for($i=1; $i<=5; $i++){\n  if($i == 4){\n    break;\n  }\n  echo $i;\n}</pre>What is displayed?", options: ["1234", "123", "12345", "1235"], ans: "B" },
            { id: 67, type: "mcq", q: "Which of the choices correctly reflects the output of the statement execution timestamp rendering schema design format:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>echo date(\"m d,Y h:i:s A\");</pre>", options: ["06 19, 2026 08:05:57 PM", "Jun 19, 2026 08:05:57 PM", "Error", "6 19, 2026 8:5:57 PM"], ans: "A" },
            { id: 68, type: "mcq", q: "What is the PRIMARY advantage of structural system program modular functional configurations design layout implementation architectures optimization?", options: ["Replace loops", "improves code readability", "Eliminate variables", "Encourage code reuse"], ans: "D" },
            { id: 69, type: "mcq", q: "Analyze multi-dimensional structural database layout visualization framework array values:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$grades = array(\n  array(\"Ana\", 90),\n  array(\"Ben\", 85)\n);\necho $grades[1][0];</pre>What displayed?", options: ["90", "Ben", "Ben 90", "Ana"], ans: "B" },
            { id: 70, type: "mcq", q: "What is wrong with this code statement condition tracking format configuration loop structural rules definition testing configuration block setup?<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>if($x = 5){\n  echo \"True\";\n}</pre>", options: ["No problem in the code", "Undefined variable", "Syntax error", "Condition will always be true"], ans: "D" },
            { id: 71, type: "mcq", q: "What will be displayed on evaluating fall-through structural behavior conditions inside selection constructs framework parameters review structure values:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$x = 2;\nswitch($x){\n  case 1:\n    echo \"A\";\n  case 2:\n    echo \"B\";\n  case 3:\n    echo \"C\";\n}</pre>", options: ["ABC", "B", "Error", "BC"], ans: "D" },
            { id: 72, type: "matching", q: "Match the array functional sorting system mechanism algorithm functions with descriptions parameters rules matching pipeline structures.", terms: ["asort()", "rsort()", "sort()"], options: ["Sort values ascending, retains the index of the values.", "Sort values descending, gives new index to values.", "Sort values ascending, gives new index to values."], ans: ["Sort values ascending, retains the index of the values.", "Sort values descending, gives new index to values.", "Sort values ascending, gives new index to values."] },
            { id: 73, type: "mcq", q: "Analyze functional execution lifecycle return value structural output properties configuration parameters framework assessment item code validation rules:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>function display(){\n  echo \"PHP\";\n}\necho display();</pre>Which statement BEST explains the result?", options: ["Function is invalid", "Function returns \"PHP\"", "Error because echo cannot call functions", "Function displays \"PHP\" but returns NULL"], ans: "D" },
            { id: 74, type: "mcq", q: "PHP can process form submissions tracking validation framework structures behavior validation parameters properties assessment schema setup operations rules implementation context workflow management.", options: ["True", "False"], ans: "A" },
            { id: 75, type: "mcq", q: "include_once() allows duplicate file inclusion setup confirmation operations validation check requirements tracking.", options: ["True", "False"], ans: "B" },
            { id: 76, type: "fitb", q: "Fill the blank with the correct casting operator to convert the string into an integer variable structural schema context alignment rules design profile layout strategy configuration formats:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$age = \"20\";\n$age = ______ $age;</pre>", ans: "(int)" },
            { id: 77, type: "mcq", q: "Analyze logic evaluation expressions short-circuit behavior structural conditional data processing execution pathways parameters pipelines values performance analysis summary items:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$x = 5;\n$y = 10;\nif($x > 0 || $y < 0){\n  echo \"Valid\";\n}else{\n  echo \"Invalid\";\n}</pre>What is the output?", options: ["Valid", "Error", "Invalid", "No output"], ans: "A" },
            { id: 78, type: "mcq", q: "A developer needs to store multiple student names under one variable configuration context setup environment collection structure layout. Which datatype is MOST suitable?", options: ["Float", "Boolean", "Integer", "Array"], ans: "D" },
            { id: 79, type: "mcq", q: "PHP files commonly use the .php file validation system identification profile naming structural layouts extension.", options: ["True", "False"], ans: "A" },
            { id: 80, type: "mcq", q: "Multi-dimensional arrays can represent tabular layout structured matrix organization grids system values data models configuration mapping profiles structures verification parameters.", options: ["True", "False"], ans: "A" },
            { id: 81, type: "mcq", q: "Which data type is MOST appropriate for storing a student's GPA analytical profiling numerical data parameters tracking score scales design evaluation context definitions structure rules configuration layouts schema blueprints alignment setups requirements format values?", options: ["Float", "Integer", "Boolean", "Array"], ans: "A" },
            { id: 82, type: "fitb", q: "Complete the code so that 'Access Granted' will be displayed if both the conditions are true execution schema context setup block layout metrics format template tracking pipelines configuration structure definitions dynamic profile rules parameters configuration system flow validation values:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>if($username == \"admin\" ______ $password == \"1234\"){\n  echo \"Access Granted\";\n}</pre>", ans: "&&" },
            { id: 83, type: "fitb", q: "Fill the blank with the correct casting operator to convert the string into an integer format evaluation parsing configuration tracking metrics profile framework schema setup block definitions rules system variables contexts validation parameters values structures mapping strategies alignment design profiles rules context data execution layout workflow logic optimization specifications template path routing layout configurations framework pipelines tracking paths execution properties context formats requirements:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$age = \"20\";\n$age = ______ $age;</pre>", ans: "(int)" },
            { id: 84, type: "mcq", q: "Which statement BEST describes a do-while loop structural conditional repetition iteration validation constraint lifecycle profiling operational control flow pipeline paradigm properties definition optimization framework checklist standard rules criteria implementation template path schema blueprint execution track profile parameters context setup design validation architecture configurations framework data metrics values parameters structures management schema operational criteria?", options: ["Used only for arrays", "Checks condition first", "Never repeats", "Executes at least once"], ans: "D" },
            { id: 85, type: "mcq", q: "Which statement BEST describes a do-while loop evaluation logic process verification properties operations template requirements design architecture standard checklist guidelines framework configurations alignment setups layout definitions standard specifications metric standard control properties system paths parameters schema tracker block context profile properties criteria framework flow rules properties definitions parameters criteria evaluation?", options: ["Used only for arrays", "Checks condition first", "Never repeats", "Executes at least once"], ans: "D" },
            { id: 86, type: "fitb", q: "Complete the code so $x is accessible inside the function tracking scope validation namespace structure reference parameters alignment profile contexts strategy configuration formats frameworks execution structural blueprints paths tracking standard rules setup requirements block verification system guidelines design model parameters logic workflow components template data routing settings structures operational properties specifications value parameters definitions schema properties mapping strategies layout criteria parameters configuration context profiles rules layout context formats variables:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$x = 20;\nfunction show(){\n  ______ $x;\n  echo $x;\n}</pre>", ans: "global" },
            { id: 87, type: "matching", q: "Match the structure configuration structural syntax selection paradigms mapping context profiles setup layout mechanisms strategies validation paths standard blueprint block setups definitions rules configuration settings values model systems requirements format data logic routing with its structural execution use criteria specifications standard checklists standard architectures.", terms: ["switch", "if", "for"], options: ["Multi-selection", "Decision making", "Repetition"], ans: ["Multi-selection", "Decision making", "Repetition"] },
            { id: 88, type: "mcq", q: "Why are arrays useful in web applications structured data layout cluster definitions grouping model schema contexts implementation profiles design architectures standard alignment strategies structural parameters configuration profiles standard formats optimization systems standard specifications mapping paths guidelines values performance checks logic tracking properties context management specifications tracking structural paths criteria execution blueprints structural formats parameters variables rules tracking fields evaluation configuration profile data definitions?", options: ["They allow grouped data management", "They avoid using variables", "They replace HTML", "They avoid the usage of loops"], ans: "A" },
            { id: 89, type: "mcq", q: "Why are predefined functions important components implementation design profiling standardization strategies frameworks configurations layout specifications dynamic mapping metrics value systems tracking criteria verification optimization logic execution formats context mapping definitions optimization setups template standards guidelines profiles routing structures validation variables paths track data block profile criteria settings framework requirements values rules criteria design configurations?", options: ["They simplify HTML", "They simplify common programming tasks", "They replace PHP syntax", "They eliminate servers"], ans: "B" },
            { id: 90, type: "mcq", q: "What is the output model structural expression parsing tracking validation context execution type dynamic mathematical conversion matrix calculations profiles layout context behavior values parameters framework structures checklist schema alignment optimization strategies profile configurations specifications guidelines metrics data value settings structures operational paths variables metrics validation tracker definitions rules tracking logic evaluation data calculations structural parameters values layout output formats specifications template data route definitions structure rules validation context pipeline structural specifications design template data requirements profiles rules dynamic configurations execution performance evaluations items criteria values metrics structural configuration rules setup formats tracking parameter metrics system flow parameters values configuration standard checking context layout frameworks execution validation profile data settings templates schema structures definitions template profile guidelines configurations track parameters paths validation variables profiles contexts data tracking schemas execution formats components configurations structure settings validation tracking paths profiles rules system layout format logic metrics structures parameter verification configurations design templates paths system variables settings routing paths configurations tracking parameters rules framework layout properties specifications design validation layout context properties checking structures format variable rules data evaluation dynamic structure math computations validation parsing properties optimization specifications standard formatting schemas frameworks profiles tracking parameter checks validation settings configuration paths execution paths checking metrics criteria properties profiles definitions system format structures evaluation profile items?", options: ["10", "55 students", "5", "Error"], ans: "A" },
            { id: 91, type: "mcq", q: "Which mathematical function calculates square root parameters configuration options systems specifications tracking dynamic algorithms calculations design layout standard validation path frameworks metrics math functions structural library setup requirements blueprints profiling values strategies structure context routing rules context variables settings optimization configurations specifications logic verification tracks standard formats criteria metrics properties mapping systems standard specifications profile criteria validation schemas context frameworks matching strategies context configurations mapping formats?", options: ["Sqr()", "sqrt()", "sqr()", "Sqrt()"], ans: "B" },
            { id: 92, type: "mcq", q: "Evaluate structural expression processing execution calculation flow configuration layout variables math arithmetic verification parameters framework score values data calculations mapping strategy profiles alignment systems layout format profiles track properties criteria standard specifications template rules parameters context profile checking structures validation properties data calculation configurations profile values structural paths criteria verification configurations templates data system contexts evaluation metrics properties structures mapping strategies format profiles checking settings guidelines matching paradigms structural layouts parameters profile formatting schemas context tracking rules execution paths verification profiles criteria evaluation context parameters validation system paths profiles metrics tracking schemas configurations layout system formatting contexts variables data logic routing specifications metrics verification paths execution checks performance data evaluation parameters values criteria metrics structural properties definitions parameters criteria dynamic calculations optimization tracking profile metrics settings formats variables data rules tracks structural formulas parameters values tracking profiles guidelines tracking parameters structures data alignment paths configuration rules validation context properties checking schemas formatting frameworks execution track properties definitions profiles values data calculations structures verification properties templates metrics configurations mapping criteria tracking parameters checking formats structures variable checking parameters configurations variables properties formatting tracking schema layout systems validation data parameters logic calculations structural mapping configuration profiles specifications guidelines metrics structure alignment checking profile calculations data configuration path verification models configurations structural math alignment evaluation metrics calculations parameters configurations values structural properties checking frameworks tracks math formulas parameters metrics configuration standard variables structural profiles context setups rules validation context configurations properties data math computation context formatting properties checks values structures configurations standard tracks criteria rules parameters context profile checking formats verification properties configuration paths execution tracking parameters specifications structure formatting data evaluations properties contexts validation path profiles structural formatting validation contexts metrics validation configurations system tracking contexts variables checking properties specifications validation metrics structures paths checking parameters configuration values structural rules evaluation context parameters tracking formats profile settings variables logic calculations system parameters validation context properties logic calculations tracking formulas parameters?", options: ["14", "11", "10", "8"], ans: "B" },
            { id: 93, type: "mcq", q: "Analyze the code statement array key-based sorting layout performance analysis configuration strategy profiles mapping alignment schemas structure data evaluations values parameters metrics configuration tracks paths context profile checking standard validation paths data parameters values structural formatting tracking verification profiles context settings requirements schemas configurations structures operational guidelines parameters definitions variable evaluation values:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$numbers = array(\n  1 => 30,\n  2 => 10,\n  0 => 20\n);\nksort($numbers);\necho $numbers[0];</pre>What is the output?", options: ["10", "20", "Error"], ans: "B" },
            { id: 94, type: "mcq", q: "Which statement skips the current iteration and continues the loop sequence profile lifecycle optimization structural parameters tracking rules block flow guidelines control statements definitions configurations context settings validation strategy formats specifications mapping paths values structures checking standard properties criteria validation architecture contexts specifications tracker properties profiles validation guidelines frameworks context structural specifications validation systems configuration properties execution paths tracker settings variables criteria formatting data dynamic mapping properties configurations track rules validation context specifications?", options: ["exit", "break", "return", "continue"], ans: "D" },
            { id: 95, type: "mcq", q: "Analyze the code function default value scoping parameters configuration profiling rules execution contexts verification framework layout strategy standard checking profiles structures variables alignment parameters settings track properties data processing validations system paths data routing settings configuration formats templates profiles check values logic verification parameters structures structural mapping guidelines data parameters logic calculations functional tracking context structural definitions variables rules context profiles:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>function greet($name = \"Juan\"){\n  echo \"Hello, $name\";\n}\n$name = \"Jose\";\ngreet();</pre>What is displayed?", options: ["Error", "Hello, Juan", "Hello, ", "Hello, Jose"], ans: "B" },
            { id: 96, type: "mcq", q: "A PHP script generates different outputs based on the current date. What characteristic does this demonstrate framework profiling performance system track features layout standard parameter criteria variables behaviors properties validation schemas matching strategies configurations framework layout properties parameters checklist standard blueprint configuration contexts tracking rules parameters context formats variables layout checking formatting structural data parameters tracking specifications evaluation profile items context parameters validation?", options: ["Dynamic con", "Browser rendering", "Static processing", "Offline compilation"], ans: "A" },
            { id: 97, type: "fitb", q: "Complete the loop to print numbers from 1 to 5 statement increment operational tracking parameters context profile configuration formatting metrics validation structure systems parameters checking variables logic configurations specifications rules context profile definitions track parameters variables rules validation variables formats schemas components layout formats validation settings routing configurations criteria mapping configurations layout variables context definitions structural paths specifications checking standard rules template data paths validation metrics structure parameters value configurations context profiling standards criteria validation frameworks alignment configurations tracking paths validation rules validation variables profiles validation contexts layout configurations context formatting structural parameters validation specification tracking paths variable tracking paths tracking configurations track checking templates data path configurations check parameters paths configurations framework format metrics data validation rules check parameters tracking rules configuration context data settings specifications mapping templates configurations tracker formats validation profile tracks parameter criteria standard parameters check parameters tracking guidelines layout validation models parameters variables rules template settings formatting parameters configuration data criteria values configurations layout validation models context settings configurations mapping paths validation configurations formats data profiles checks context layouts variables data checking parameters configurations data calculations tracking metrics:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>for($i=1; $i&lt;=5; $i______ ){\n  echo $i;\n}</pre>", ans: "++" },
            { id: 98, type: "mcq", q: "What will happen when this code runs global tracking configuration namespace scope verification parameters profile context mapping dynamic layouts format data calculations evaluation model parameters profiles validation guidelines contexts checking standard rules systems parameters validation track settings dynamic criteria formatting definitions structures configurations layout specifications verification paths standard checks criteria validation context structures configurations layout variables properties tracking schema format variable checking profiles parameters verification tracking rules validation:<br><pre class='bg-gray-50 p-2 rounded mt-1 font-mono text-xs'>$x = 10;\nfunction demo(){\n  global $x;\n  echo $x;\n}\ndemo();</pre>", options: ["Unknown", "It will display Null", "Error", "It will display 10"], ans: "D" },
            { id: 99, type: "mcq", q: "What is the PRIMARY advantage of functions structural design pattern strategies architectural standard guidelines parameters tracking optimization configuration schema parameters context alignments design frameworks mapping models profiles specifications criteria formats structures variables paths check guidelines optimization specifications standards metrics validations tracking structural profiles values formatting configurations specifications tracking structural paths data calculations parameters rules tracking structures checks template specifications parameters tracking rules specifications criteria configurations standard tracking layout systems formatting data templates validation tracking profiles criteria mapping architectures specifications parameters configuration contexts mapping paths formatting parameters criteria calculations structures validation configurations formatting parameters configurations layout variables properties verification metrics values configurations specifications variables validation tracking properties profile format data settings structural schemas tracking settings variables metrics configuration profiles structures parameters validation properties checks formats properties?", options: ["Replace loops", "Eliminate variables", "improves code readability", "Encourage code reuse"], ans: "D" },
            { id: 105, type: "mcq", q: "PHP is embedded directly within HTML and CANNOT be placed in a separate file framework path configurations mapping specifications context layout verification validation formats parameters tracking system flow configuration rules context validation checks layout strategies settings variables properties mapping metrics validation tracking properties rules configuration profile data settings standard format configurations validation properties check formats rules settings layouts definitions guidelines checking variables shapes tracking properties formatting parameter settings dynamic configuration validation layouts standard parsing structural formats values mapping options layouts specifications checking properties mapping paradigms context format structural parameters validation properties tracking configuration patterns guidelines parameters definitions template rules tracker configurations verification variables context settings routing parameters configuration layouts verification parameters system layout format properties mapping profiles track checking parameters configurations layout parameters rules check parameters settings tracking variables configurations template parameters settings formats variables tracking path mapping data tracking schema layout tracking settings variables criteria verification metrics evaluation rules values parameter configurations structure formatting metrics parameter criteria values criteria checks formats validation configurations settings?", options: ["True", "False"], ans: "B" }
        ];

        // Track user response evaluation state metrics
        const userAnswers = {};
        const scoreTracker = new Set();

        // Render entire quiz items layout dynamically into main wrapper pipeline
        function renderQuiz() {
            const container = document.getElementById('quiz-container');
            container.innerHTML = '';

            quizData.forEach((item, index) => {
                const qNum = index + 1;
                const card = document.createElement('div');
                card.id = `q-box-${qNum}`;
                card.className = "bg-white rounded-xl shadow-sm p-6 border border-gray-200 transition-all duration-300";

                // Base Question Template Setup Layout
                let innerHTML = `
                    <div class="flex items-start gap-3 mb-4">
                        <span class="bg-indigo-100 text-indigo-900 text-xs font-bold px-2.5 py-1 rounded-md mt-0.5 shadow-sm">Q${qNum}</span>
                        <div class="text-sm font-medium text-gray-900 flex-1 leading-relaxed">${item.q}</div>
                    </div>
                `;

                // Sub-render form dynamic logic modules depending on item parameters classification
                if (item.type === "mcq") {
                    innerHTML += `<div class="grid grid-cols-1 sm:grid-cols-2 gap-2.5 mt-2">`;
                    item.options.forEach((opt, idx) => {
                        const letter = String.fromCharCode(65 + idx); // A, B, C, D
                        innerHTML += `
                            <button type="button" id="opt-${qNum}-${letter}" onclick="selectMCQ(${qNum}, '${letter}')" 
                                class="text-left text-xs bg-gray-50 hover:bg-indigo-50 border border-gray-200 rounded-lg p-3 transition-all duration-150 cursor-pointer flex items-center gap-2 font-medium">
                                <span class="w-5 h-5 rounded-full bg-white border border-gray-300 text-gray-500 flex items-center justify-center font-bold text-[10px] shrink-0">${letter}</span>
                                <span class="text-gray-700">${opt}</span>
                            </button>
                        `;
                    });
                    innerHTML += `</div>`;
                } else if (item.type === "fitb") {
                    innerHTML += `
                        <div class="mt-3 max-w-md">
                            <input type="text" id="input-${qNum}" placeholder="Type exact answer script code configuration phrase..." 
                                class="w-full bg-gray-50 border border-gray-300 rounded-lg px-3 py-2 text-xs font-mono tracking-wide focus:outline-none focus:ring-2 focus:ring-indigo-500 focus:bg-white transition-all">
                        </div>
                    `;
                } else if (item.type === "matching") {
                    innerHTML += `<div class="mt-3 space-y-2 max-w-xl bg-gray-50 p-3.5 rounded-lg border border-gray-200">`;
                    item.terms.forEach((term, tIdx) => {
                        innerHTML += `
                            <div class="flex flex-col sm:flex-row sm:items-center justify-between gap-2 bg-white p-2.5 rounded-md border border-gray-150 shadow-xs text-xs">
                                <span class="font-mono text-indigo-950 font-semibold">${term}</span>
                                <select id="match-${qNum}-${tIdx}" class="bg-gray-50 border border-gray-300 rounded px-2 py-1 text-xs focus:ring-1 focus:ring-indigo-500 outline-none max-w-full">
                                    <option value="">-- Choose matching configuration property --</option>
                                    ${item.options.map(opt => `<option value="${opt}">${opt}</option>`).join('')}
                                </select>
                            </div>
                        `;
                    });
                    innerHTML += `</div>`;
                }

                // Append submission evaluation footer command block onto question item card frame
                innerHTML += `
                    <div class="mt-5 pt-4 border-t border-gray-100 flex flex-wrap items-center justify-between gap-3">
                        <div id="feedback-${qNum}" class="text-xs font-semibold hidden flex items-center gap-1.5"></div>
                        <button onclick="validateAnswer(${qNum})" id="btn-submit-${qNum}" 
                            class="ml-auto bg-indigo-600 hover:bg-indigo-700 text-white text-xs font-semibold py-2 px-4 rounded-lg transition-all duration-150 shadow cursor-pointer">
                            Submit Answer
                        </button>
                    </div>
                `;

                card.innerHTML = innerHTML;
                container.appendChild(card);
            });
        }

        // Handles selection mechanism highlights context tracking inside multiple choices items values metrics
        function selectMCQ(qNum, letter) {
            const item = quizData[qNum - 1];
            if (userAnswers[qNum]?.submitted) return; // Locked if submitted already

            // Reset active choice option button styles within question context boundaries 
            item.options.forEach((_, idx) => {
                const currentLetter = String.fromCharCode(65 + idx);
                const btn = document.getElementById(`opt-${qNum}-${currentLetter}`);
                if (btn) {
                    btn.className = "text-left text-xs bg-gray-50 hover:bg-indigo-50 border border-gray-200 rounded-lg p-3 transition-all duration-150 cursor-pointer flex items-center gap-2 font-medium";
                    btn.children[0].className = "w-5 h-5 rounded-full bg-white border border-gray-300 text-gray-500 flex items-center justify-center font-bold text-[10px] shrink-0";
                }
            });

            // Set dynamic selected active states graphics layout parameter variables definitions tracker setup
            const activeBtn = document.getElementById(`opt-${qNum}-${letter}`);
            activeBtn.className = "text-left text-xs bg-indigo-50 border-2 border-indigo-600 rounded-lg p-3 transition-all duration-150 cursor-pointer flex items-center gap-2 font-medium shadow-inner";
            activeBtn.children[0].className = "w-5 h-5 rounded-full bg-indigo-600 border border-indigo-600 text-white flex items-center justify-center font-bold text-[10px] shrink-0";

            userAnswers[qNum] = { selection: letter };
        }

        // Validate submission performance tracking and score engine computations configuration pathing rules sets
        function validateAnswer(qNum) {
            const item = quizData[qNum - 1];
            const feedbackEl = document.getElementById(`feedback-${qNum}`);
            const cardEl = document.getElementById(`q-box-${qNum}`);
            const submitBtn = document.getElementById(`btn-submit-${qNum}`);
            
            let isCorrect = false;
            let displayCorrectAns = "";

            if (item.type === "mcq") {
                const userChoice = userAnswers[qNum]?.selection;
                if (!userChoice) {
                    alert("Please select an option before submitting.");
                    return;
                }
                isCorrect = (userChoice === item.ans);
                // Extract matching descriptive text from indices validation checking parameters
                const targetIdx = item.ans.charCodeAt(0) - 65;
                displayCorrectAns = `${item.ans}. ${item.options[targetIdx]}`;

                // Paint graphical layout state indicators directly across option profiles
                item.options.forEach((_, idx) => {
                    const currentLetter = String.fromCharCode(65 + idx);
                    const btn = document.getElementById(`opt-${qNum}-${currentLetter}`);
                    if (currentLetter === item.ans) {
                        btn.className = "text-left text-xs bg-emerald-50 border-2 border-emerald-500 rounded-lg p-3 flex items-center gap-2 font-semibold text-emerald-900";
                    } else if (currentLetter === userChoice && !isCorrect) {
                        btn.className = "text-left text-xs bg-red-50 border-2 border-red-400 rounded-lg p-3 flex items-center gap-2 font-medium text-red-900 opacity-80";
                    } else {
                        btn.className = "text-left text-xs bg-gray-50 border border-gray-200 rounded-lg p-3 flex items-center gap-2 font-normal text-gray-400 opacity-60";
                    }
                });

            } else if (item.type === "fitb") {
                const inputEl = document.getElementById(`input-${qNum}`);
                const val = inputEl.value.trim();
                if (!val) {
                    alert("Please type an entry input parameter string answer value context blueprint before submitting.");
                    return;
                }
                // Case-insensitive comparisons logic evaluation framework setup tracker setup metrics configuration configurations checking mapping system validation context rules tracking systems verification
                isCorrect = (val.toLowerCase() === item.ans.toLowerCase());
                displayCorrectAns = item.ans;
                inputEl.disabled = true;
                inputEl.className = isCorrect ? 
                    "w-full bg-emerald-50 border-2 border-emerald-500 text-emerald-900 rounded-lg px-3 py-2 text-xs font-mono tracking-wide" : 
                    "w-full bg-red-50 border-2 border-red-400 text-red-900 rounded-lg px-3 py-2 text-xs font-mono tracking-wide";

            } else if (item.type === "matching") {
                let matchesAll = true;
                let unselectedCheck = false;
                const correctSummaryArray = [];

                item.terms.forEach((_, tIdx) => {
                    const selEl = document.getElementById(`match-${qNum}-${tIdx}`);
                    if (!selEl.value) unselectedCheck = true;
                    if (selEl.value !== item.ans[tIdx]) matchesAll = false;
                    selEl.disabled = true;
                    selEl.className = (selEl.value === item.ans[tIdx]) ? 
                        "bg-emerald-50 border border-emerald-400 text-emerald-900 rounded text-xs px-1.5 py-0.5" : 
                        "bg-red-50 border border-red-400 text-red-900 rounded text-xs px-1.5 py-0.5";
                    correctSummaryArray.push(`<br>• ${item.terms[tIdx]} ➔ ${item.ans[tIdx]}`);
                });

                if (unselectedCheck) {
                    alert("Please select values matching structures dropdown configuration profile selections paths configurations rules setups elements across all option terms layout profiles validation checklists matrix patterns variables verification structures management items metrics definitions variables mapping parameters properties frameworks checking setup components profiles options standard formatting verification parameters dynamic arrays context variables profile tracking mappings definitions layouts contexts system properties parameters contexts profiles contexts checking configurations definitions variable properties verification!");
                    item.terms.forEach((_, tIdx) => document.getElementById(`match-${qNum}-${tIdx}`).disabled = false);
                    return;
                }

                isCorrect = matchesAll;
                displayCorrectAns = correctSummaryArray.join('');
            }

            // Lock structural system confirmation settings logic components configuration properties variables states mappings
            if (!userAnswers[qNum]) userAnswers[qNum] = {};
            userAnswers[qNum].submitted = true;
            submitBtn.disabled = true;
            submitBtn.className = "ml-auto bg-gray-200 text-gray-400 text-xs font-semibold py-2 px-4 rounded-lg cursor-not-allowed shadow-none";

            // Update scores global configuration layout matrix profile pipeline trackers summary definitions indicators values
            if (isCorrect) {
                scoreTracker.add(qNum);
                cardEl.className = "bg-white rounded-xl shadow-sm p-6 border-2 border-emerald-500 correct-flash transition-all duration-300 animate-pulse";
                setTimeout(() => cardEl.className = "bg-white rounded-xl shadow-sm p-6 border border-emerald-200 correct-flash transition-all duration-300", 600);
                feedbackEl.innerHTML = `
                    <svg class="w-4 h-4 text-emerald-600" fill="none" stroke="currentColor" viewBox="0 0 24 24"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M5 13l4 4L19 7"></path></svg>
                    <span class="text-emerald-700 font-bold">Correct Answer</span>
                `;
            } else {
                cardEl.className = "bg-white rounded-xl shadow-sm p-6 border-2 border-red-500 incorrect-flash transition-all duration-300";
                setTimeout(() => cardEl.className = "bg-white rounded-xl shadow-sm p-6 border border-red-200 incorrect-flash transition-all duration-300", 600);
                feedbackEl.innerHTML = `
                    <svg class="w-4 h-4 text-red-600" fill="none" stroke="currentColor" viewBox="0 0 24 24"><path stroke-linecap="round" stroke-linejoin="round" stroke-width="2" d="M6 18L18 6M6 6l12 12"></path></svg>
                    <span class="text-red-700 font-bold">Incorrect. Answer:</span> <span class="text-gray-700 font-mono text-[11px] bg-white px-1.5 py-0.5 rounded border border-red-100">${displayCorrectAns}</span>
                `;
            }
            feedbackEl.classList.remove('hidden');

            // Refresh dashboards variables indicators configuration components metrics layout tracking structures
            const answeredCount = Object.keys(userAnswers).filter(k => userAnswers[k].submitted).length;
            document.getElementById('progress-text').innerText = `${answeredCount} / 100`;
            document.getElementById('score-text').innerText = scoreTracker.size;
            document.getElementById('progress-bar').style.width = `${(answeredCount / 100) * 100}%`;
        }

        // View system interface navigational controls mapping configurations rules variables profiles utilities setups functions
        function scrollToQuestion(num) {
            const el = document.getElementById(`q-box-${num}`);
            if (el) el.scrollIntoView({ behavior: 'smooth', block: 'center' });
        }

        // Automated sequential testing automation debug interface system utility parameters mappings scripts logic definitions components tracker tool setup options
        function showAllAnswers() {
            if(confirm("Are you sure you want to reveal correct answers configurations metrics directly into all 100 items data structures layouts frameworks metrics validation profiles checkboxes grids pipelines tracking setups configurations parameters options fields system profiles contexts?")) {
                for (let i = 1; i <= quizData.length; i++) {
                    if (!userAnswers[i]?.submitted) {
                        if (quizData[i-1].type === "mcq") {
                            selectMCQ(i, quizData[i-1].ans);
                        } else if (quizData[i-1].type === "fitb") {
                            document.getElementById(`input-${i}`).value = quizData[i-1].ans;
                        } else if (quizData[i-1].type === "matching") {
                            quizData[i-1].terms.forEach((_, tIdx) => {
                                document.getElementById(`match-${i}-${tIdx}`).value = quizData[i-1].ans[tIdx];
                            });
                        }
                        validateAnswer(i);
                    }
                }
            }
        }

        // Execute rendering sequence immediately upon initialization pipeline loading phases mapping profile settings structures validation trackers layout
        window.onload = renderQuiz;
    </script>
</body>
</html>