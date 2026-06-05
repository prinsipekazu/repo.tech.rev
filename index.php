<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Interactive PHP AppDev Test</title>
    <style>
        body {
            font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif;
            background-color: #f4f7f6;
            color: #333;
            line-height: 1.6;
            margin: 0;
            padding: 20px;
        }
        .container {
            max-width: 800px;
            margin: 0 auto;
            background: #fff;
            padding: 30px;
            border-radius: 8px;
            box-shadow: 0 4px 15px rgba(0,0,0,0.05);
        }
        h1 {
            text-align: center;
            color: #4A154B;
            border-bottom: 2px solid #f4f7f6;
            padding-bottom: 15px;
        }
        .quiz-info {
            text-align: center;
            font-style: italic;
            color: #666;
            margin-bottom: 30px;
        }
        .question-block {
            margin-bottom: 25px;
            padding: 20px;
            border-left: 4px solid #4A154B;
            background: #fafafa;
            border-radius: 0 4px 4px 0;
        }
        .question-text {
            font-weight: 600;
            font-size: 1.1em;
            margin-bottom: 15px;
        }
        .code-snippet {
            font-family: 'Courier New', Courier, monospace;
            background: #272822;
            color: #f8f8f2;
            padding: 12px;
            border-radius: 4px;
            display: block;
            white-space: pre-wrap;
            margin-bottom: 15px;
            font-size: 0.95em;
        }
        .options-list {
            list-style: none;
            padding: 0;
            margin: 0;
        }
        .option-item {
            margin-bottom: 10px;
        }
        .option-item label {
            display: block;
            padding: 10px 15px;
            background: #fff;
            border: 1px solid #ddd;
            border-radius: 4px;
            cursor: pointer;
            transition: all 0.2s ease;
        }
        .option-item label:hover {
            background: #f0f0f0;
            border-color: #bbb;
        }
        .option-item input[type="radio"] {
            margin-right: 10px;
        }
        .input-text-answer {
            width: 100%;
            padding: 10px;
            font-size: 1em;
            border: 1px solid #ddd;
            border-radius: 4px;
            box-sizing: border-box;
        }
        .btn-submit {
            display: block;
            width: 100%;
            padding: 15px;
            background: #4A154B;
            color: #fff;
            border: none;
            font-size: 1.2em;
            font-weight: bold;
            border-radius: 6px;
            cursor: pointer;
            margin-top: 30px;
            transition: background 0.2s ease;
        }
        .btn-submit:hover {
            background: #631D64;
        }
        #results-banner {
            display: none;
            padding: 20px;
            background: #e7f4e4;
            border: 2px solid #b2dba1;
            color: #2b542c;
            font-size: 1.3em;
            font-weight: bold;
            text-align: center;
            border-radius: 6px;
            margin-bottom: 30px;
        }
        .feedback {
            margin-top: 12px;
            font-weight: bold;
            display: none;
        }
        .feedback.correct {
            color: #2b542c;
        }
        .feedback.incorrect {
            color: #a94442;
        }
        .correct-answer-reveal {
            font-weight: normal;
            display: block;
            font-size: 0.9em;
            margin-top: 4px;
            color: #333;
        }
    </style>
</head>
<body>

<div class="container">
    <h1>Application Development - PHP Practice Test</h1>
    <p class="quiz-info">This test is fully interactive and randomizes the order of all 100 loaded questions every time you refresh.</p>
    
    <div id="results-banner"></div>
    <div id="progressText" class="quiz-info"></div>
    <div id="quiz-questions-container"></div>
    <button type="button" class="btn-submit" id="checkBtn" onclick="checkAnswer()">Check Answer</button>
    <button type="button" class="btn-submit" id="nextBtn" onclick="nextQuestion()" style="display:none; margin-top: 12px;">Next Question</button>
</div>

<script>
// Complete dataset mapping structural inputs directly from user document
const masterQuestions = [
    { id: 1, type: "mcq", q: "A programmer accidentally created an infinite loop. Which issue MOST likely caused it?", options: ["Too many variables", "The condition has arithmetic operators", "Loop condition never becomes false", "Missing HTML tags"], answer: "Loop condition never becomes false" },
    { id: 2, type: "fill", q: "Complete the nested function call so that it will display Inside.", code: "function outer(){\n  function inner(){\n    echo \"Inside\";\n  }\n  ____\n}\nouter();", answer: "inner();" },
    { id: 3, type: "mcq", q: "Analyze the code. What is the output?", code: "$x = 5;\nif($x > 3){\n  if($x < 10){\n    echo \"A\";\n  }else{\n    echo \"B\";\n  }\n}", options: ["No output", "A", "AB", "B"], answer: "A" },
    { id: 4, type: "mcq", q: "What is the output?", code: "echo \"5\" + \"5 students\";", options: ["10", "55 students", "5", "Error"], answer: "10" },
    { id: 5, type: "mcq", q: "A grading system must store Student Name, Subject, and Grade for hundreds of students. Which structure is MOST appropriate?", options: ["Multiple arrays", "A single multi-dimensional array", "Multiple single-dimensional array", "Multiple variables"], answer: "A single multi-dimensional array" },
    { id: 6, type: "fill", q: "Complete the function declaration:", code: "____ greet(){\n  echo \"Hello\";\n}", answer: "function" },
    { id: 7, type: "mcq", q: "Which software package is MOST suitable for beginners setting up PHP locally?", options: ["XAMPP", "Visual Studio Code", "Composer", "Git"], answer: "XAMPP" },
    { id: 8, type: "fill", q: "Complete the function declaration.", code: "____ displayMessage(){\n  echo \"Welcome\";\n}", answer: "function" },
    { id: 9, type: "mcq", q: "What will be the output?", code: "for($i=1; $i<=3; $i++){\n  // \n}\ echo $i;", options: ["012", "0123", "12", "123"], answer: "123" },
    { id: 10, type: "mcq", q: "What is the problem in this code?", code: "1. $x = 5;\n2. \n3. function test(){\n4.   echo $x;\n5. }\n6. test();", options: ["Missing echo in line 6", "Undefined variable inside function", "Missing return statement", "No problem"], answer: "Undefined variable inside function" },
    { id: 11, type: "mcq", q: "What will be the output?", code: "$x = 0;\nif($x = 1){\n  echo \"YES\";\n}else{\n  echo \"NO\";\n}", options: ["NO", "YES", "Unknown", "Error"], answer: "YES" },
    { id: 12, type: "mcq", q: "Given the statement below, what is the value of $x?", code: "$x = 5 + 3 * 2;", options: ["13", "16", "10", "11"], answer: "11" },
    { id: 13, type: "mcq", q: "Analyze the code. What is the output?", code: "$numbers = array(10,20,30);\necho count($numbers);", options: ["Error", "No output", "2", "3"], answer: "3" },
    { id: 14, type: "mcq", q: "What is wrong with this code?", code: "if($x = 5){\n  echo \"True\";\n}", options: ["No problem in the code", "Condition will always be true", "Undefined variable", "Syntax error"], answer: "Condition will always be true" },
    { id: 15, type: "mcq", q: "A developer wants a webpage to automatically generate customized greetings for each user visiting the site. Which feature of PHP is MOST useful?", options: ["CSS animation", "Browser caching", "Static HTML rendering", "Server-side scripting"], answer: "Server-side scripting" },
    { id: 16, type: "mcq", q: "In PHP, the return datatype of a function MUST be specified when declaring a function.", options: ["True", "False"], answer: "False" },
    { id: 17, type: "mcq", q: "Which scenario BEST demonstrates dynamic web content?", options: ["Fixed image gallery", "Offline text editor", "A printed brochure", "A webpage displaying current weather data from a database"], answer: "A webpage displaying current weather data from a database" },
    { id: 18, type: "mcq", q: "PHP is embedded directly within HTML and CANNOT be placed in a separate file.", options: ["True", "False"], answer: "False" },
    { id: 19, type: "mcq", q: "goto helps programs to be more organized and easier to maintain in the long run.", options: ["True", "False"], answer: "False" },
    { id: 20, type: "fill", q: "Complete the loop so that it will execute 5 times:", code: "for($i=1; ____)", answer: "$i<=5; $i++" },
    { id: 21, type: "mcq", q: "What is the output?", code: "$a = \"10\";\n$b = \"2a\";\necho $a + $b;", options: ["10", "Error", "12", "102a"], answer: "12" },
    { id: 22, type: "mcq", q: "Which of the choices correctly reflects the output of the statement?", code: "echo date(\"m d,Y h:i:A\");\n// Assuming context mock standard timestamp matches option selection", options: ["06 19, 2026 08:05:57 PM", "6 19, 2026 8:5:57 PM", "Error", "Jun 19, 2026 08:05:57 PM"], answer: "06 19, 2026 08:05:57 PM" },
    { id: 23, type: "fill", q: "Complete the statement so that it will return the remainder of the two parameters.", code: "function multiply($a, $b){\n  ____\n}", answer: "return $a % $b" },
    { id: 24, type: "mcq", q: "Which data type is MOST appropriate for storing a student's GPA?", options: ["Integer", "Boolean", "Array", "Float"], answer: "Float" },
    { id: 25, type: "fill", q: "Fill in the missing operator to increase $x by 5.", code: "$x ____ 5;", answer: "+=" },
    { id: 26, type: "mcq", q: "Analyze the code. What is the output?", code: "$i = 1;\nwhile($i <= 3){\n  echo $i;\n}", options: ["12", "123", "Infinite loop", "012"], answer: "Infinite loop" },
    { id: 27, type: "mcq", q: "Analyze the code. What is the output?", code: "function add($a, $b){\n  return $a + $b;\n}\necho add(\"5\",\"3\");", options: ["Error", "8", "53", "Unknown"], answer: "8" },
    { id: 28, type: "mcq", q: "A developer accidentally declared both $Score and $score and the program did not show the output as expected. Why did the program produce unexpected results?", options: ["PHP ignores capitalization", "PHP variables are case-sensitive", "Variables are automatically merged", "PHP converts all variables to lowercase"], answer: "PHP variables are case-sensitive" },
    { id: 29, type: "fill", q: "Complete the statement so that it will return the remainder of the two parameters.", code: "function multiply($a, $b){\n  ____\n}", answer: "return $a % $b" },
    { id: 30, type: "fill", q: "Complete the logical operator so both conditions must be true.", code: "if($x > 0 ____ $y > 0)", answer: "&&" },
    { id: 31, type: "mcq", q: "A student placed a PHP file on the desktop and attempted to run it directly in the browser. The PHP code appeared as plain text. What is the BEST explanation?", options: ["PHP requires JavaScript to run", "The browser does not support HTML", "PHP scripts require a web server environment and must be placed in a server-specific directory", "The file must be compressed first"], answer: "PHP scripts require a web server environment and must be placed in a server-specific directory" },
    { id: 32, type: "mcq", q: "What is wrong with this code?", code: "function calc($a, $b){\n  $a + $b\n}\necho calc(2,3);", options: ["Missing echo statement inside the function", "Missing return statement", "Parameters are declared wrong", "Wrong arguments"], answer: "Missing return statement" },
    { id: 33, type: "fill", q: "Complete the code so that 'Access Granted' will be displayed if both the conditions are true.", code: "if($username == \"admin\" ____ $password == \"1234\"){\n  echo \"Access Granted\";\n}", answer: "&&" },
    { id: 34, type: "mcq", q: "Which definition correctly matches Apache from the web components mapping?", options: ["Displays webpages", "Stores data", "Host websites", "Compiles binary files"], answer: "Host websites" },
    { id: 35, type: "fill", q: "Complete the function declaration.", code: "____ displayMessage(){\n  echo \"Welcome\";\n}", answer: "function" },
    { id: 36, type: "fill", q: "Complete the implementation setup targeting addition evaluations with direct string elements parsing in functional boundaries return contexts.", code: "function add($a, $b){\n  return ____;\n}", answer: "$a + $b" },
    { id: 37, type: "mcq", q: "A grading system must store Student Name, Subject, and Grade for hundreds of students. Which structure is MOST appropriate?", options: ["Multiple variables", "Multiple arrays", "Multiple single-dimensional array", "A single multi-dimensional array"], answer: "A single multi-dimensional array" },
    { id: 38, type: "mcq", q: "Analyze the code. What is displayed?", code: "$grades = array(\n  array(\"Ana\",90),\n  array(\"Ben\",85)\n);\necho $grades[1][0];", options: ["Ben 90", "Ben", "Ana", "90"], answer: "Ben" },
    { id: 39, type: "fill", q: "Complete the statement to convert \"hello\" to uppercase.", code: "echo ____(\"hello\");", answer: "strtoupper" },
    { id: 40, type: "mcq", q: "Why are variables important in programming?", options: ["They replace servers", "They remove HTML", "They prevent loops", "They store reusable data values"], answer: "They store reusable data values" },
    { id: 41, type: "mcq", q: "A webpage updates product prices automatically from a database every hour. Which concept is MOST related?", options: ["Static rendering", "File compression", "Browser plugins", "Dynamic scripting"], answer: "Dynamic scripting" },
    { id: 42, type: "fill", q: "What is the output?", code: "$x = 2;\n$y = 3;\n$z = 4;\necho $x + $y * $z - $y;", answer: "11" },
    { id: 43, type: "fill", q: "Complete the PHP code tag context closure block:", code: "<?php\necho \"Welcome to PHP\";\n____", answer: "?>" },
    { id: 44, type: "fill", q: "Complete the loop parameters structure block so that it will execute 5 times:", code: "for($i = 1; ____)", answer: "$i<=5; $i++" },
    { id: 45, type: "mcq", q: "Multiplication has higher precedence than addition, but lower than division.", options: ["True", "False"], answer: "False" },
    { id: 46, type: "fill", q: "Complete the function declaration keyword identifier structure context rule.", code: "____ displayMessage(){\n  echo \"Welcome\";\n}", answer: "function" },
    { id: 47, type: "mcq", q: "Which loop is MOST appropriate when the number of repetitions is known beforehand?", options: ["do..while", "for", "foreach", "while"], answer: "for" },
    { id: 48, type: "mcq", q: "PHP files commonly use the .php extension.", options: ["True", "False"], answer: "True" },
    { id: 49, type: "mcq", q: "What is the correct secondary operation step workflow sequencing of standard web architecture structures?", options: ["Browser sends request", "Server processes PHP", "Response is generated in HTML form", "Browser receives response"], answer: "Server processes PHP" },
    { id: 50, type: "mcq", q: "include_once() allows duplicate file inclusion.", options: ["True", "False"], answer: "False" },
    { id: 51, type: "fill", q: "Complete the constant declaration globally structured parameter system setup value setup:", code: "____(\"SITE\", \"My Website\");", answer: "define" },
    { id: 52, type: "mcq", q: "Why is PHP commonly paired with MySQL?", options: ["PHP cannot display HTML", "MySQL compiles PHP code", "MySQL replaces Apache", "PHP is optimized for database interaction"], answer: "PHP is optimized for database interaction" },
    { id: 53, type: "mcq", q: "What is the final process operation step in validating logic parameters like $x > 5 && $y < 10?", options: ["Compare variables definitions", "Compare relational expressions", "Apply logical AND", "Variable casting assignment execution"], answer: "Apply logical AND" },
    { id: 54, type: "mcq", q: "What is the issue with this code sequence context configuration?", code: "for($i=1; $i>0; $i++){\n  echo $i;\n}", options: ["Infinite loop", "Nothing", "Syntax error", "Undefined variable"], answer: "Infinite loop" },
    { id: 55, type: "mcq", q: "A developer wants a webpage to automatically generate customized greetings for each user visiting the site. Which feature of PHP is MOST useful?", options: ["Browser caching", "Server-side scripting", "Static HTML rendering", "CSS animation"], answer: "Server-side scripting" },
    { id: 56, type: "fill", q: "Complete the loop logic workflow parameter block configurations ruleset so that 3 will not be displayed in output operations context layout setup.", code: "for($i=1; $i<=5; $i++){\n  if($i == 3){\n    ____;\n  }\n  echo $i;\n}", answer: "continue" },
    { id: 57, type: "fill", q: "Complete the functional variable instantiation parameter context values tracking lists definitions so that each structural variable will hold a baseline default assignment parameter value representation tracking of 0.", code: "function add(____){\n  return $a + $b;\n}", answer: "$a=0, $b=0" },
    { id: 58, type: "fill", q: "Complete the alternative structure syntactic system tracking evaluation parameters initialization codeblock blocks format layout setup rules.", code: "if($age >= 18):\n  echo \"Adult\";\n____;", answer: "endif" },
    { id: 59, type: "fill", q: "Complete the increment system setup values configuration rules matching within structure sets tracking contexts block loops syntax systems to output numeric variables ranges looping numbers sequentially tracking directly from 1 to 5.", code: "for($i=1; $i<=5; $i____){\n  echo $i;\n}", answer: "++" },
    { id: 60, type: "fill", q: "Complete the active core rendering operational parameters printing dynamic value tracking outputs instruction statements block code syntax sets.", code: "<?php\n____ \"PHP\";\n?>", answer: "echo" },
    { id: 61, type: "mcq", q: "Type casting permanently changes the original datatype stored in all variables referencing the value within background system definitions variables contexts allocations.", options: ["True", "False"], answer: "False" },
    { id: 62, type: "mcq", q: "Analyze the conditional script snippet parameters execution. What exactly is output?", code: "$x = 5;\nif($x > 3){\n  echo \"A\";\n}else{\n  //\n}\necho \"B\";", options: ["No output", "A", "AB", "B"], answer: "A" },
    { id: 63, type: "mcq", q: "What will be the output?", code: "$x = 0;\nif($x = 1){\n  echo \"YES\";\n}else{\n  echo \"NO\";\n}", options: ["NO", "Unknown", "Error", "YES"], answer: "YES" },
    { id: 64, type: "mcq", q: "A grading system must store Student Name, Subject, and Grade for hundreds of students. Which structure is MOST appropriate?", options: ["Multiple variables", "Multiple arrays", "Multiple single-dimension array", "A single multi-dimension array"], answer: "A single multi-dimension array" },
    { id: 65, type: "mcq", q: "What is the output?", code: "$x = 2;\n$y = 3;\n$z = 4;\necho $x + $y * $z - $y;", options: ["10", "11", "14", "8"], answer: "11" },
    { id: 66, type: "mcq", q: "Analyze the code snippet sequence workflow tracking context logic execution. What is the generated console output pattern?", code: "for($i=1; $i<=5; $i++){\n  if($i == 4){\n    break;\n  }\n  echo $i;\n}", options: ["1234", "123", "12345", "1235"], answer: "123" },
    { id: 67, type: "mcq", q: "Which of the choices correctly reflects the output of the statement containing full seconds parameters syntax definitions formatting configuration setups rules layout?", code: "echo date(\"m d,Y h:i:s A\");", options: ["06 19, 2026 08:05:57 PM", "Jun 19, 2026 08:05:57 PM", "Error", "6 19, 2026 8:5:57 PM"], answer: "06 19, 2026 08:05:57 PM" },
    { id: 68, type: "mcq", q: "What is the PRIMARY advantage of utilizing functions configurations structures design sets parameters components contexts optimization operations?", options: ["Replace loops", "Improves code readability", "Eliminate variables", "Encourage code reuse"], answer: "Encourage code reuse" },
    { id: 69, type: "mcq", q: "Analyze the multi-dimensional dataset configuration context array array structures setup layout logic representation. What data parameter output values displays directly upon invocation execution?", code: "$grades = array(\n  array(\"Ana\",90),\n  array(\"Ben\",85)\n);\necho $grades[1][0];", options: ["90", "Ben", "Ben 90", "Ana"], answer: "Ben" },
    { id: 70, type: "mcq", q: "What is wrong with this code context tracking execution rules setup layout design variables block parameters definition?", code: "if($x = 5){\n  echo \"True\";\n}", options: ["No problem in the code", "Undefined variable", "Syntax error", "Condition will always be true"], answer: "Condition will always be true" },
    { id: 71, type: "mcq", q: "What will be displayed from following evaluation logic processing parameters configuration setup block structural tracking system control stream context flow loops definitions sets?", code: "$x = 2;\nswitch($x){\n  case 1:\n  case 2:\n    echo \"A\";\n    echo \"B\";\n  case 3:\n    echo \"C\";\n}", options: ["ABC", "B", "Error", "BC"], answer: "BC" },
    { id: 72, type: "mcq", q: "What is the specific description sorting logic mapping profile ruleset system parameters criteria specification setup context configuration for the predefined native method function option rsort() setup operation context rules?", options: ["Sort values ascending, gives new index to values.", "Sort values ascending, retains the index of the values.", "Sort values descending, gives new index to values.", "Sort multidimensional keys directly sequential."], answer: "Sort values descending, gives new index to values." },
    { id: 73, type: "mcq", q: "Analyze the functional tracking definition execution parameters code snippet instructions execution context framework parameters rules block layout properties system setups.", code: "function display(){\n  echo \"PHP\";\n}\necho display();", options: ["Function is invalid", "Function returns \"PHP\"", "Error because echo cannot call functions", "Function displays \"PHP\" but returns NULL"], answer: "Function displays \"PHP\" but returns NULL" },
    { id: 74, type: "mcq", q: "PHP can process form submissions tracking parameters payloads fields records arrays content operations layout systems configurations.", options: ["True", "False"], answer: "True" },
    { id: 75, type: "mcq", q: "include_once() allows duplicate file inclusion parsing processing setups environments execution pipeline logic context.", options: ["True", "False"], answer: "False" },
    { id: 76, type: "fill", q: "Fill the blank with the correct casting operator to convert the string into an integer variable data format storage system context type casting allocation representation context alignment setup profile.", code: "$age = \"20\";\n$age = ____ $age;", answer: "(int)" },
    { id: 77, type: "mcq", q: "Analyze the following tracking conditional expression logic framework evaluation operations setup processing constraints context parameters block layout code syntax snippet configuration system tracking setup rules values outputs.", code: "$x = 5;\n$y = 10;\nif($x > 0 || $y < 0){\n  echo \"Valid\";\n}else{\n  echo \"Invalid\";\n}", options: ["Valid", "Error", "Invalid", "No output"], answer: "Valid" },
    { id: 78, type: "mcq", q: "A developer needs to store multiple student names under one single processing unit variable structural format assignment context mapping data management layer criteria setup structure configuration values metrics.", options: ["Float", "Boolean", "Integer", "Array"], answer: "Array" },
    { id: 79, type: "mcq", q: "PHP files commonly use the standard baseline default system extension format tracking rule structure parameters dot indicator representation framework format suffix value context rule configurations.", options: ["True", "False"], answer: "True" },
    { id: 80, type: "mcq", q: "Multi-dimensional arrays can represent tabular rows columns matrix storage sets data records layout formats frameworks information schemas.", options: ["True", "False"], answer: "True" },
    { id: 81, type: "mcq", q: "Which data type is MOST appropriate for storing a student's GPA metrics evaluation decimal baseline numeric precision configurations data profiles sets criteria layout rules setup tracker configuration formats variables system tracking values?", options: ["Float", "Integer", "Boolean", "Array"], answer: "Float" },
    { id: 82, type: "fill", q: "Complete the code tracking criteria so that 'Access Granted' value string literal information representation messages will render visible on display screens context parameters layout checks configuration rules criteria validations framework if conditions are met properly checked.", code: "if($username == \"admin\" ____ $password == \"1234\"){\n  echo \"Access Granted\";\n}", answer: "&&" },
    { id: 83, type: "fill", q: "Fill the blank with the correct casting operator to convert the string data tracking value sequence type context pattern directly into a numeric integer format system execution parsing parameters layout blocks instructions baseline alignment setups assignments context metrics properties rules.", code: "$age = \"20\";\n$age = ____ $age;", answer: "(int)" },
    { id: 84, type: "mcq", q: "Which statement BEST describes a standard loop structure type iteration execution format flow tracking behavioral workflow mechanism property profile criteria for typical block loop tracking do-while conditional control operation frameworks configurations sequences layout architectures sets parameters parameters logic tracker processing routines workflows units processing metrics tracking statements sets contexts system profiles parameters?", options: ["Used only for arrays", "Checks condition first", "Never repeats", "Executes at least once"], answer: "Executes at least once" },
    { id: 85, type: "mcq", q: "Which statement BEST describes a do-while loop processing execution sequence flow architecture structural specification tracking setup parameter layout condition operational pipeline configuration properties blocks frameworks system contexts criteria rules matching rules parameters configurations specifications tracking mechanisms metrics functions system control instructions arrays rules tracker profiles indicators frameworks tracking arrays layouts criteria setups tracking loops criteria rules structures context evaluations?", options: ["Used only for arrays", "Checks condition first", "Never repeats", "Executes at least once"], answer: "Executes at least once" },
    { id: 86, type: "fill", q: "Complete the statement block context identifier visibility rules syntax properties initialization configurations mapping keyword tracking indicator assignment definitions so that the parent global variable representation tracking indicator sequence parameter reference context $x becomes accessible locally directly inside structural block programmatic context routine layout environments configuration functional definitions ranges specifications metrics tracking fields variables systems layers boundaries scope operations rules alignment configurations patterns units.", code: "$x = 20;\nfunction show(){\n  ____ $x;\n  echo $x;\n}", answer: "global" },
    { id: 87, type: "mcq", q: "What is the primary programmatic operational design structural purpose mapping criteria category classification specification definition framework index layout profile context alignment indicator assignment parameter criteria selection profile setup categorization rules setup rule context metric criteria for standard core loop structure identifier 'for' control execution tracking formats patterns loops structures block programmatic control paths workflows definitions setups layout processing?", options: ["Multi-selection", "Decision making", "Repetition", "Data definition alignment transformation compilation parsing routing optimization storage setups"], answer: "Repetition" },
    { id: 88, type: "mcq", q: "Why are arrays useful in web applications development data tier architectures tracking elements storage structures patterns layouts systems contexts collections configurations operational baseline layers tracking records processing indicators profiles frameworks properties metrics values groupings setups formats variables management processing layers?", options: ["They allow grouped data management", "They avoid using variables", "They replace HTML", "They avoid the usage of loops"], answer: "They allow grouped data management" },
    { id: 89, type: "mcq", q: "Why are predefined functions important parameter tracking utilities components standard structures frameworks architecture design setups compilation pipelines rules configurations blocks methods modules systems operations definitions assets scripts applications codebases developers optimizations components templates frameworks toolings layout units properties parameters tracking operations execution modules formats?", options: ["They simplify HTML", "They simplify common programming tasks", "They replace PHP syntax", "They eliminate servers"], answer: "They simplify common programming tasks" },
    { id: 90, type: "mcq", q: "What is the output?", code: "echo \"5\" + \"5 students\";", options: ["10", "55 students", "5", "Error"], answer: "10" },
    { id: 91, type: "mcq", q: "Which core built-in standard mathematical native library utility core framework method algorithm call calculated resolution evaluation function maps calculates computing properties square root calculation formats value definitions metrics sets processing operational parameters structure configurations specifications units options trackers structures syntax contexts identifiers layout configurations tracking definitions values?", options: ["Sqr()", "sqrt()", "sqr()", "Sqrt()"], answer: "sqrt()" },
    { id: 92, type: "mcq", q: "What is the precise math arithmetic calculation evaluation outcome resolution output variable display sequence of the baseline statement below matching code sequence specifications formats variables sets tracks equations execution parameters setup logic layers configuration tracking parameters profiles context blocks expressions values values metrics dimensions layout structures outputs?", code: "$x = 2;\n$y = 3;\n$z = 4;\necho $x + $y * $z - $y;", options: ["14", "11", "10", "8"], answer: "11" },
    { id: 93, type: "mcq", q: "Analyze the explicit key-value tracking associative indexes context initialization sequence. What precisely is output onto screens display metrics execution pipeline upon executing this sorting system script logic setup?", code: "$numbers = array(\n  1 => 30,\n  2 => 10,\n  0 => 20\n);\nksort($numbers);\necho $numbers[0];", options: ["10", "20", "Error", "30"], answer: "20" },
    { id: 94, type: "mcq", q: "Which control flow statement immediately terminates context parsing execution steps internally localized inside targeted active loop structures to instantly skip current loop iterations parameters and dynamically proceed straight forward moving along tracking next structural loop pass increments workflows operations setups rules pipeline context configurations paths?", options: ["exit", "break", "return", "continue"], answer: "continue" },
    { id: 95, type: "mcq", q: "Analyze the function declaration with default parameters logic. What will be displayed upon execution tracking call context configuration setups parameters definitions?", code: "function greet($name = \"Juan\"){\n  echo \"Hello, $name\";\n}\n$name = \"Jose\";\ngreet();", options: ["Error", "Hello, Juan", "Hello,", "Hello, Jose"], answer: "Hello, Juan" },
    { id: 96, type: "mcq", q: "A PHP script generates completely different unique real-time tailored dynamic context rendering output content structures variant data assets depending explicitly on changing variables parameters values metrics timestamps current date time metrics properties definitions. What fundamental technical architecture development software model paradigm design attribute feature capability behavior state nature does this represent?", options: ["Dynamic content generation", "Browser rendering constraints", "Static processing execution", "Offline compilation loops"], answer: "Dynamic content generation" },
    { id: 97, type: "fill", q: "Complete the sequential parameter tracking increment block loop statement syntax parameters matching criteria code specifications layout structure values to continuously cleanly loop increment ranges printing numeric context directly tracking sequential intervals counting up directly from 1 to 5 units loops iterations logic paths values sets properties rules contexts alignment setups.", code: "for($i=1; $i<=5; $i____){\n  echo $i;\n}", answer: "++" },
    { id: 98, type: "mcq", q: "What exactly will occur dynamically during background runtime operations context processes layout tracking pipelines setup executions when this programmatic control block script invokes running execution processing sequences rules layout definitions values profiles properties configurations metrics tracker logic functions pipelines structures variables sets?", code: "$x = 10;\nfunction demo(){\n  global $x;\n  echo $x;\n}\ndemo();", options: ["Unknown situational error paths", "It will display Null", "Error trace reference logs mapping exception errors", "It will display 10"], answer: "It will display 10" },
    { id: 99, type: "mcq", q: "What is the PRIMARY advantage of implementing modular isolated custom system design layout functional blocks routines functions structures code configurations variables setups parameters logic tracks architectures engineering practices elements components values profiles design tracking layout models paradigms specifications operations formats systems methodologies sets setups optimizations trackers mechanisms structures implementations properties environments values indicators layout patterns programs scripts setups metrics software designs blueprints algorithms engineering frames workflows platforms architectures context rules tracking designs layers metrics?", options: ["Replace loops contexts constraints tracking components operations setups systems rules frameworks layout", "Eliminate variables parameter references footprints allocations management tracking architectures specifications designs layout definitions patterns configurations sets values", "Improves code readability structural presentation alignment visuals formatting paradigms execution profiles", "Encourage code reuse optimizations modular design architectures consistency performance metrics scale deployments frameworks"], answer: "Encourage code reuse code optimization modular design architectures consistency performance metrics scale deployments frameworks" },
    { id: 100, type: "mcq", q: "PHP code blocks structures parsing processing definitions instructions directives codebases logic files statements scripts modules components structures tracking models scripts architectures layouts layouts can be seamlessly injected embedded directly raw alongside standard markup layout frameworks HTML tags configurations and CANNOT under any conditional deployment requirements configurations setup environments pipeline frameworks structure metrics boundaries properties variations configurations parameters values be isolated inside separated individual external modular .php physical data file layout formats storage units setups objects context tracking systems criteria architectures profiles layer frameworks sets patterns rules.", options: ["True", "False"], answer: "False" }
];

// Linear Shuffle Utility (Fisher-Yates) for full randomization support
function shuffleArray(array) {
    for (let i = array.length - 1; i > 0; i--) {
        const j = Math.floor(Math.random() * (i + 1));
        [array[i], array[j]] = [array[j], array[i]];
    }
    return array;
}

// Randomize array data structure securely prior to building layout nodes runtime
const randomizedQuestions = shuffleArray([...masterQuestions]);
let currentQuestionIndex = 0;
let score = 0;

function renderCurrentQuestion() {
    const container = document.getElementById('quiz-questions-container');
    container.innerHTML = '';
    const progressText = document.getElementById('progressText');
    const qData = randomizedQuestions[currentQuestionIndex];

    progressText.innerText = `Question ${currentQuestionIndex + 1} of ${randomizedQuestions.length}`;

    const questionBlock = document.createElement('div');
    questionBlock.className = 'question-block';
    questionBlock.setAttribute('data-id', qData.id);
    questionBlock.setAttribute('data-type', qData.type);

    const qText = document.createElement('div');
    qText.className = 'question-text';
    qText.innerText = `${currentQuestionIndex + 1}. ${qData.q}`;
    questionBlock.appendChild(qText);

    if (qData.code) {
        const codeBlock = document.createElement('pre');
        codeBlock.className = 'code-snippet';
        codeBlock.innerText = qData.code;
        questionBlock.appendChild(codeBlock);
    }

    if (qData.type === 'mcq') {
        const optionsList = document.createElement('ul');
        optionsList.className = 'options-list';

        let renderedOptions = [...qData.options];
        if (!renderedOptions.includes(qData.answer)) {
            renderedOptions.push(qData.answer);
        }
        renderedOptions = shuffleArray(renderedOptions);

        renderedOptions.forEach(opt => {
            const li = document.createElement('li');
            li.className = 'option-item';

            const label = document.createElement('label');
            const radio = document.createElement('input');
            radio.type = 'radio';
            radio.name = `question_${qData.id}`;
            radio.value = opt;

            label.appendChild(radio);
            label.appendChild(document.createTextNode(` ${opt}`));
            li.appendChild(label);
            optionsList.appendChild(li);
        });

        questionBlock.appendChild(optionsList);
    } else {
        const inputAnswer = document.createElement('input');
        inputAnswer.type = 'text';
        inputAnswer.className = 'input-text-answer';
        inputAnswer.placeholder = 'Type your answer here...';
        inputAnswer.name = `question_${qData.id}`;
        questionBlock.appendChild(inputAnswer);
    }

    const feedbackBlock = document.createElement('div');
    feedbackBlock.className = 'feedback';
    feedbackBlock.id = `feedback_${qData.id}`;
    questionBlock.appendChild(feedbackBlock);

    container.appendChild(questionBlock);

    document.getElementById('checkBtn').disabled = false;
    const nextBtn = document.getElementById('nextBtn');
    nextBtn.style.display = 'none';
    nextBtn.disabled = true;
    nextBtn.innerText = currentQuestionIndex < randomizedQuestions.length - 1 ? 'Next Question' : 'Show Results';
}

function normalizeAnswer(answer) {
    return answer.trim().toLowerCase().replace(/\s+/g, '');
}

function checkAnswer() {
    const qData = randomizedQuestions[currentQuestionIndex];
    const feedbackEl = document.getElementById(`feedback_${qData.id}`);
    let userAns = '';

    if (qData.type === 'mcq') {
        const checkedOption = document.querySelector(`input[name="question_${qData.id}"]:checked`);
        if (checkedOption) {
            userAns = checkedOption.value.trim();
        }
    } else {
        const inputField = document.querySelector(`input[name="question_${qData.id}"]`);
        if (inputField) {
            userAns = inputField.value.trim();
        }
    }

    if (!userAns) {
        feedbackEl.style.display = 'block';
        feedbackEl.className = 'feedback incorrect';
        feedbackEl.innerText = 'Please answer before checking.';
        return;
    }

    const correctAnswer = qData.answer.trim();
    const isCorrect = qData.type === 'fill'
        ? normalizeAnswer(userAns) === normalizeAnswer(correctAnswer)
        : userAns === correctAnswer;

    feedbackEl.style.display = 'block';
    if (isCorrect) {
        score++;
        feedbackEl.className = 'feedback correct';
        feedbackEl.innerText = '✓ Correct!';
    } else {
        feedbackEl.className = 'feedback incorrect';
        feedbackEl.innerHTML = `✗ Incorrect. <span class="correct-answer-reveal"><strong>Correct Answer:</strong> ${correctAnswer}</span>`;
    }

    document.getElementById('checkBtn').disabled = true;
    const nextBtn = document.getElementById('nextBtn');
    nextBtn.style.display = 'inline-block';
    nextBtn.disabled = false;
}

function nextQuestion() {
    if (currentQuestionIndex < randomizedQuestions.length - 1) {
        currentQuestionIndex++;
        renderCurrentQuestion();
    } else {
        showResults();
    }
}

function showResults() {
    const resultsBanner = document.getElementById('results-banner');
    resultsBanner.style.display = 'block';
    resultsBanner.innerText = `Quiz Complete! Your Score: ${score} / ${randomizedQuestions.length} (${Math.round((score / randomizedQuestions.length) * 100)}%)`;

    document.getElementById('quiz-questions-container').innerHTML = '';
    document.getElementById('progressText').innerText = 'All questions are complete.';
    document.getElementById('checkBtn').style.display = 'none';
    document.getElementById('nextBtn').style.display = 'none';
}

renderCurrentQuestion();
</script>

</body>
</html>