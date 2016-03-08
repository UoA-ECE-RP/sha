<?php

$opt_level = "2";
$dir = getcwd();

function CSVToArray($fp) {
	$headers = Array();
	$array = Array();
	if(($data = fgetcsv($fp)) !== false) {
		$num = count($data);
		for ($i=0; $i<$num; $i++)
			$headers[$i] = $data[$i];
	}
	
	if((sizeof($headers) == 0) || strpos($headers[0], 'html')) {
		fclose($fp);
		return $array;
	}
	
	$j = 0;
	while(($data = fgetcsv($fp)) !== false) {
		$num = count($data);
		for ($i=0; $i<$num; $i++)
			$array[$j][$headers[$i]] = $data[$i];
		$j++;
	}
	
	fclose($fp);
	return $array;
}

function delTree($dir, $include_dir = true) {
	$files = array_diff(scandir($dir), array('.','..'));

	foreach ($files as $file) {
		is_dir("$dir/$file") ? delTree("$dir/$file") : unlink("$dir/$file");
	}

	if($include_dir) {
		return rmdir($dir);
	}
}

$makefile = fopen("Makefile", "w");

fwrite($makefile, "all: build\n\n");

$items = Array();
$headers = Array();

if(is_dir("Cells/Generated")) {
	delTree("Cells/Generated", false);
}
else {
	mkdir("Cells/Generated");
}

if(is_dir("Paths/Generated")) {
	delTree("Paths/Generated", false);
}
else {
	mkdir("Paths/Generated");
}

if(is_file("Cells/cells.csv")) {
	$fp = fopen("Cells/cells.csv", "r");

	$data = CSVToArray($fp);

	foreach($data as $cell) {
		$safe_name = str_replace("-", "", $cell["Name"]);
		$filename = "Cell3d_" . $cell["Neighbours"] . "input";

		if(is_file("Cells/" . $filename . ".c") && is_file("Cells/" . $filename . ".h")) {
			$c_contents = file_get_contents("Cells/" . $filename . ".c");

			foreach($cell as $key => $value) {
				$c_contents = str_replace($key, $value, $c_contents);
			}

			$c_contents = str_replace($filename, $safe_name, $c_contents);

			file_put_contents("Cells/Generated/" . $safe_name . ".c", $c_contents);

			$h_contents = file_get_contents("Cells/" . $filename . ".h");

			foreach($cell as $key => $value) {
				$h_contents = str_replace($key, $value, $h_contents);
			}

			$h_contents = str_replace($filename, $safe_name, $h_contents);
			$h_contents = str_replace(strtoupper($filename), strtoupper($safe_name), $h_contents);

			file_put_contents("Cells/Generated/" . $safe_name . ".h", $h_contents);

			$items[] = $safe_name;
			$headers[] = "Cells/Generated/" . $safe_name . ".h";
			fwrite($makefile, "Objects/" . $safe_name . ": Cells/Generated/" . $safe_name . ".c Generic/step.h\n");
			fwrite($makefile, "\t@echo Building " . $cell["Name"] . "...\n");
			fwrite($makefile, "\t@cl /c /O" . $opt_level . " Cells/Generated/" . $safe_name . ".c /Fo" . $dir . "\\Objects\\" . $safe_name . "\n");
			fwrite($makefile, "\n");
		}
		else {
			echo "Warning: Unable to find a cell to create with " . $cell["Neighbours"] . " neighbours!!!!\n";
		}
	}	
}

if(is_file("Paths/paths.csv")) {
	$fp = fopen("Paths/paths.csv", "r");

	$data = CSVToArray($fp);

	foreach($data as $path) {
		$safe_name = str_replace("-", "", $path["Name"]);
		if(is_file("Paths/Path.c") && is_file("Paths/Path.h")) {
			$c_contents = file_get_contents("Paths/Path.c");

			foreach($path as $key => $value) {
				$c_contents = str_replace($key, $value, $c_contents);
			}

			$c_contents = str_replace("Path", $safe_name, $c_contents);

			file_put_contents("Paths/Generated/" . $safe_name . ".c", $c_contents);

			$h_contents = file_get_contents("Paths/Path.h");

			foreach($path as $key => $value) {
				$h_contents = str_replace($key, $value, $h_contents);
			}

			$h_contents = str_replace("Path", $safe_name, $h_contents);
			$h_contents = str_replace(strtoupper("Path"), strtoupper($safe_name), $h_contents);

			file_put_contents("Paths/Generated/" . $safe_name . ".h", $h_contents);

			$items[] = $safe_name;
			$headers[] = "Paths/Generated/" . $safe_name . ".h";
			fwrite($makefile, "Objects/" . $safe_name . ": Paths/Generated/" . $safe_name . ".c Generic/step.h\n");
			fwrite($makefile, "\t@echo Building " . $path["Name"] . "...\n");
			fwrite($makefile, "\t@cl /c /O" . $opt_level . " Paths/Generated/" . $safe_name . ".c /Fo" . $dir . "\\Objects\\" . $safe_name . "\n");
			fwrite($makefile, "\n");
		}
		else {
			echo "Warning: Unable to find a path to create!!!!\n";
		}
	}
}

$runnable = fopen("runnable.c", "w");

fwrite($runnable, "#include <stdint.h>\n");
fwrite($runnable, "#include <stdlib.h>\n");
fwrite($runnable, "#include <stdio.h>\n");
fwrite($runnable, "#include <string.h>\n");
fwrite($runnable, "#include <stdint.h> // portable: uint64_t   MSVC: __int64
#include <Windows.h>

	
int gettimeofday(struct timeval * tp, struct timezone * tzp)
{
    // Note: some broken versions only have 8 trailing zero's, the correct epoch has 9 trailing zero's
    static const uint64_t EPOCH = ((uint64_t) 116444736000000000ULL);

    SYSTEMTIME  system_time;
    FILETIME    file_time;
    uint64_t    time;
	
	GetSystemTime( &system_time );
    SystemTimeToFileTime( &system_time, &file_time );
    time =  ((uint64_t)file_time.dwLowDateTime )      ;
    time += ((uint64_t)file_time.dwHighDateTime) << 32;

    tp->tv_sec  = (long) ((time - EPOCH) / 10000000L);
    tp->tv_usec = (long) (system_time.wMilliseconds * 1000);
    return 0;
}\n");
fwrite($runnable, "\n");
fwrite($runnable, "#include \"Generic/step.h\"\n");
foreach($headers as $header) {
	fwrite($runnable, "#include \"" . $header . "\"\n");	
}
fwrite($runnable, "\n");

foreach($items as $item) {
	fwrite($runnable, "" . $item . " " . $item . "_data;\n");
}
fwrite($runnable, "\n");

fwrite($runnable, "int main(void) {\n");
foreach($items as $item) {
	fwrite($runnable, "\t(void) memset((void *)&" . $item . "_data, 0, sizeof(" . $item . "));\n");
	fwrite($runnable, "\t" . $item . "Init(&" . $item . "_data);\n");
	fwrite($runnable, "\n");
}

fwrite($runnable, "\tFILE* fo = fopen(\"out.csv\", \"w\");\n");
fwrite($runnable, "\n");

fwrite($runnable, "\tstruct timeval t0, t1;\n");
fwrite($runnable, "\tgettimeofday(&t0, 0);\n");
fwrite($runnable, "\n");

fwrite($runnable, "\tunsigned int i = 0;\n");
fwrite($runnable, "\tfor(i=0; i < (SIMULATION_TIME / STEP_SIZE); i++) {\n");
fwrite($runnable, "\t\t//fprintf(stdout, \"Time: %fms\\n\", i*STEP_SIZE);\n");
fwrite($runnable, "\t\t//fflush(stdout);\n");

if(is_file("custom_code.c")) {
	fwrite($runnable, "\n");
	fwrite($runnable, trim(file_get_contents("custom_code.c")));
	fwrite($runnable, "\n");
}

foreach($items as $item) {
	fwrite($runnable, "\n");
	fwrite($runnable, "\t\t" . $item . "Run(&" . $item . "_data);\n");
}

fwrite($runnable, "\t}\n");
fwrite($runnable, "\n");

fwrite($runnable, "\tgettimeofday(&t1, 0);\n");
fwrite($runnable, "\tlong elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;\n");
fwrite($runnable, "\n");
fwrite($runnable, "\tprintf(\"Time taken: %ld microseconds (%.3f seconds)\\n\", elapsed, (elapsed / 1000000.0));\n");
fwrite($runnable, "\n");

fwrite($runnable, "\tfclose(fo);\n");
fwrite($runnable, "\n");

fwrite($runnable, "\treturn 0;\n");
fwrite($runnable, "}\n");

fclose($runnable);

fwrite($makefile, "runnable: runnable.c Generic/step.h\n");
fwrite($makefile, "\t@echo Building Runnable...\n");
fwrite($makefile, "\t@cl /O" . $opt_level . " runnable.c ");
foreach($items as $item) {
	fwrite($makefile, "Objects/" . $item . ".obj ");
}
fwrite($makefile, "/Fe\n");

fwrite($makefile, "build: ");
foreach($items as $item) {
	fwrite($makefile, "Objects/" . $item . " ");
}
fwrite($makefile, "runnable");
fwrite($makefile, "\n\n");

fwrite($makefile, "clean:\n");
fwrite($makefile, "\t@echo Removing compiled binaries...\n");
foreach($items as $item) {
	fwrite($makefile, "\t@rm -r Objects/" . $item . "\n");
}
fwrite($makefile, "\t@rm -r runnable\n");
fwrite($makefile, "\n");

fclose($makefile);

?>