#include<iostream>
#include<fstream>
#include<string> 
using namespace std;


void re_assign(string**& groups, string**& groups_copy, string**& second_copy,int& group_rows,int*& group_cols)
{
	for (int i = 0; i < group_rows; i++)
	{
		for (int j = 0; j < group_cols[i]; j++)
		{
			groups[i][j] = second_copy[i][j];
			groups_copy[i][j] = second_copy[i][j];
		}
	}
}


void file_reading(string& address,string**& nums,string**&groups,int& nums_rows,int*& nums_cols,int& group_rows,int*& group_cols)
{

	fstream obj(address);
	char bracket;
	
	
	//===========================================================================================================
	//CALCULATING SIZE OF GROUP ARRAYS
	//===========================================================================================================


	while (obj >> bracket)
		if (bracket == '}')
			group_rows++;

	group_rows--;
	group_cols = new int[group_rows];
	obj.close();


	bool temp = false;
	int items = 0, i = 0;
	obj.open(address);

	while (obj >> bracket)
	{

		if (bracket == '{' && !temp)
			temp = true;

		if (bracket == '{' && temp)
		{
			string a;
			obj >> bracket;
			while (bracket != '}')
			{
				if (bracket == ',') 
					items++;
				
				obj >> bracket;
			}
			items++;
			group_cols[i] = items;
			items = 0;
			i++;
		}
	}
	obj.close();

	
	//===========================================================================================================
	//CREATING THE DYNAMIC ARRAY FOR GROUPS
	//===========================================================================================================


	groups = new string * [group_rows];
	for (int i = 0; i < group_rows; i++) 
		groups[i] = new string[group_cols[i]];
	



	//===========================================================================================================
	//CALCULATING SIZE OF NUMS ARRAYS
	//===========================================================================================================

	obj.open(address);
	bracket = ' ';

	while (obj >> bracket)
		if (bracket == ']')
			nums_rows++;

	obj.close();


	nums = new string * [nums_rows];

	nums_cols = new int[nums_rows];

	i = items = 0;
	obj.open(address);
	bracket = ' ';
	while (obj >> bracket)
	{
		if (bracket == '[')
		{

			while (bracket != ']' and bracket != 'T')
			{
				if (bracket == ',')
					items++;
				obj >> bracket;

			}
		}
		if (bracket == ']')
		{
			items++;
			nums_cols[i] = items;
			items = 0;
			i++;
		}
	}

	obj.close();



	//===========================================================================================================
	//CREATING THE DYNAMIC ARRAY FOR GROUPS
	//===========================================================================================================

	for (int i = 0; i < nums_rows; i++)
		nums[i] = new string[nums_cols[i]];




	//===========================================================================================================
	//STORING ELEMENTS OF THE GROUPS ARRAY
	//===========================================================================================================
	obj.open(address);
	char buffer;
	bool flag = 0;
	int first = 0, second = 0, brackets = 0;
	string element;

	while (obj >> buffer)
	{

		if (flag && buffer == '{')
		{
			obj >> buffer >> buffer;
			if (buffer == '}') 
			{
				second = 0;
				first++;
			}
			while (buffer != '}')
			{
				if (first == group_rows)
					break;

				while (buffer != '{' && buffer != ',' && buffer != '}')
				{
					if (buffer != 39)
						element += buffer;
					obj >> buffer;
				}

				if (element != "")
					groups[first][second] = element;

				brackets = group_cols[first] - 1;
				if (element != "" && brackets != second )
					second++;

				element = "";
				if (buffer == '}')
				{
					first++;
					second = 0;
				}
				obj >> buffer;
			}
		}
		if (buffer == '{' && !flag)
			flag = true;
	}

	obj.close();



	//===========================================================================================================
	//STORING ELEMENTS OF THE NUMS ARRAY
	//===========================================================================================================

	
	buffer = ' ';
	element = "";
	first = second = 0;

	obj.open(address);
	while (obj >> buffer)
	{
		if (buffer == '[') 
		{
			if (buffer == ']') 
			{
				second = 0;
				first++;
			}

			while (buffer != ']' && buffer != 'T')
			{
				if (first == nums_rows)
					break;

				while (buffer != 'T' && buffer != ','  && buffer != ']')
				{
					if (buffer > 0 && buffer != '[' && buffer != ']' && buffer != 39)
						element += buffer;
					obj >> buffer;
				}


				if (element != "")
					nums[first][second] = element;
	
				bracket = nums_cols[first] - 1;
				
				if (element != "" && bracket != second )
					second++;
					
		
				if (buffer == ']') 
					obj >> buffer;
			
				if (buffer == 'T') 
				{
					second = 0;
					first++;
				

					while (buffer != '[')
						obj >> buffer;
				}

				element = "";
				obj >> buffer;
			}
		}
		if (buffer == ']')
			break;

	}
	obj.close();
}


int partitioning(int starting_index, int ending_index,int arr[])
{
	int pivot = arr[starting_index], count = 0, pivotIndex;
	
	for (int i = starting_index + 1; i <= ending_index; i++)
		if (arr[i] <= pivot)
			count++;

	pivotIndex = starting_index + count;
	swap(arr[pivotIndex], arr[starting_index]);

	
	int i = starting_index, j = ending_index;

	while (i < pivotIndex && j > pivotIndex) 
	{

		while (arr[i] <= pivot) 
			i++;

		while (arr[j] > pivot) 
			j--;


		if (i < pivotIndex && j > pivotIndex) 
			swap(arr[i++], arr[j--]);
	}

	return pivotIndex;
}

void quickSort(int starting_index, int ending_index, int arr[])
{

	if (starting_index >= ending_index)
		return;

	int p = partitioning(starting_index, ending_index, arr);

	quickSort(starting_index, p - 1, arr);
	
	quickSort(p + 1, ending_index, arr);
}


void arrayinvert(string*& text,int& text_size)
{
	string temp;
	for (int i = 0,j = text_size - 1; i < text_size / 2; i++, j--)
	{
		temp = text[i];
		text[i] = text[j];
		text[j] = temp;
	}
}


bool string_matching(string*& text, string*& pattern,string*& pattern_copy, int& text_size, int& pattern_size,int checker)
{
	int matches = 0;
	int start_index = 0;
	int end_index = 0;
	int* indexes = new int[pattern_size] {0};
	int temp = 0;
	bool flag = true;

	

	for (int i = 0; i < text_size; i++)
		for (int j = 0; j < pattern_size; j++)
			if (text[i] == pattern[j])
			{
				indexes[j] = i;
				end_index = i;
				pattern[j] = "-";
				matches++;
			}


	start_index = end_index - pattern_size + 1;

	quickSort(0, pattern_size - 1, indexes);



	for (int i = 0; i < (pattern_size - 1); i++)
		if (indexes[i] + 1 != indexes[i + 1])
		{
			flag = false;
			break;
		}

	if (matches == pattern_size && flag)
	{
		for (int i = start_index; i <= end_index; i++)
			text[i] = to_string(i);
		return true;
	}
	else
	{
		bool check = false;
		if (checker == 1)
		{
			checker++;
			arrayinvert(text, text_size);
			check = string_matching(text, pattern_copy, pattern, text_size, pattern_size, checker);
			arrayinvert(text, text_size);
		}

		if (!check)
			return false;

		else 
			return true;

	}

}

bool mymain(string*&nums, string**& groups, string**& groups_copy, int& nums_size, int& group_rows, int*& group_cols)
{
	int checker = 1;
	bool* matches = new bool [group_rows] {0};
	bool flag = true;


	for (int i = 0; i < group_rows; i++)
		matches[i] = string_matching(nums, groups[i], groups_copy[i], nums_size, group_cols[i], checker);
		

	for (int i = 0; i < group_rows; i++)
	{
		if (matches[i] == 0)
			flag = false;
	}

	if (flag)
	{
		cout << "Groups are found in the given nums array" << endl;
		return true;
	}
	else
	{
		cout << "Groups are not found in the given nums array" << endl;
		return false;
	} 

}



int main()
{		  
	string** nums;
	int nums_rows = 0;
	int* nums_cols = 0;

	string** groups; 
	string** groups_copy;
	string** second_copy;

	int group_rows = 0;
	int* group_cols = 0;
	

	string address = "C:\\Users\\alium\\Desktop\\P1.txt";
	file_reading(address,nums,groups,nums_rows,nums_cols,group_rows,group_cols);
	
	groups_copy = new string * [group_rows];
	second_copy = new string * [group_rows];
	for (int i = 0; i < group_rows; i++)
	{
		groups_copy[i] = new string[group_cols[i]];
		second_copy[i] = new string[group_cols[i]];
	}


	for (int i = 0; i < group_rows; i++)
	{
		for (int j = 0; j < group_cols[i]; j++)
		{
			groups_copy[i][j] = groups[i][j];
			second_copy[i][j] = groups[i][j];
		}
	}
	

	for (int i = 0; i < nums_rows; i++)
	{
		mymain(nums[i], groups, groups_copy, nums_cols[i], group_rows, group_cols);
		re_assign(groups, groups_copy, second_copy,group_rows,group_cols);
	}
	
	return 0;
}



