#include <iostream>
#include <cassert>
#include <string>
#include <algorithm>
using namespace std;

int separate(string a[], int n, string separator);
int lookupAny(const string a1[], int n1, const string a2[], int n2);
int subsequence(const string a1[], int n1, const string a2[], int n2);
int differ(const string a1[], int n1, const string a2[], int n2);
int flip(string a[], int n);
int countRuns(const string a[], int n);
int rotateLeft(string a[], int n, int pos);
int positionOfMax(const string a[], int n);
int lookup(const string a[], int n, string target);
int appendToAll(string a[], int n, string value);




int main() {
	string h[7] = { "melania", "kamala", "donald", "tim", "", "doug", "jd" };
	assert(lookup(h, 7, "doug") == 5);
	assert(lookup(h, 7, "donald") == 2);
	assert(lookup(h, 2, "donald") == -1);
	assert(positionOfMax(h, 7) == 3);

	string g[4] = { "melania", "kamala", "jd", "usha" };
	assert(differ(h, 4, g, 4) == 2);
	assert(appendToAll(g, 4, "?") == 4 && g[0] == "melania?" && g[3] == "usha?");
	assert(rotateLeft(g, 4, 1) == 1 && g[1] == "jd?" && g[3] == "kamala?");

	string e[4] = { "donald", "tim", "", "doug" };
	assert(subsequence(h, 7, e, 4) == 2);

	string d[5] = { "kamala", "kamala", "kamala", "tim", "tim" };
	assert(countRuns(d, 5) == 2);

	string f[3] = { "jd", "donald", "gwen" };
	assert(lookupAny(h, 7, f, 3) == 2);
	assert(flip(f, 3) == 3 && f[0] == "gwen" && f[2] == "jd");

	assert(separate(h, 7, "jd") == 3);

	cout << "All tests succeeded" << endl;
}
	

int appendToAll(string a[], int n, string value) {
	// returns -1 if n(the size of the array) is less than or equal to 0.
	if (n <= 0){
		return -1;
	
	}
	// iterates through all of the values in the array a[], appending value to each of them.
	for (int i = 0; i < n; i++) {
		a[i] += value;
	
	}
	return n;

}

int lookup(const string a[], int n, string target) {

	

	int repeat = 0;
	int position = -1;
	// iterates through array of values in a[], and assigns the position of the value that is equal to target to the pos variable. Will only assign the position if there are no repeats.
	for (int i = 0; i < n; i++) {
		if (a[i] == target && repeat == 0) {
			repeat++;
			position = i;
		}

		// if there are duplicate values in the array, add 1 to repeat, and don't change the value of the position.
		else if (a[i] == target) {
			repeat++;
		}
	}
	return position;
}
int positionOfMax(const string a[], int n) {
	// returns -1 if the value of n(size of array a[]) is less than or equal to 0.
	if ( n<= 0) {
		return -1;
	}
	string s = a[0];
	int pos = 0;

	//iterates through all the values in the array, if the elemnt's value as a string is greater than another string, then it will assign that string as the new max.
	for (int i = 0; i < n; i++) {
		if (a[i].compare(s) > 0) {
			s = a[i];
			pos = i;
		}

	}
	return pos;

}




int countRuns(const string a[], int n) {


	if (n <= 0) {
		return -1;

	}

	// initializes count as 1, as there is already 1 value in the array.
	int count = 1;

	// iterates through intire list , starting at index 1, and checks if the value before it is equal to it. If the value is equal, add 1 to count, if not continue with the for loop until it iterates through all values.
	for (int i = 1; i < n; i++) {
		if (a[i] != a[i - 1]) {
			count++;
		}
		else{
			continue;
		}


	}
	return count;
}


int differ(const string a1[], int n1, const string a2[], int n2) {
	
	if (n1 < 0 || n2 < 0) {
		return -1;

	}
	
	// assigns the minimum value that we have to iterate through the array using the minimum function.
	int s = min(n1, n2);

	//if there exist values that are not equal to one another in both arrays, then it returns the first position where both values are not equal in both arrays.
	for (int i = 0; i < s; i++) {
		if (a1[i] !=  a2[i]) {
			return i;
		}
	}

	//returns the length of the array with the least elements if both arrays are valid.
	return s;
}

int lookupAny(const string a1[], int n1, const string a2[], int n2) {
	int pos = -1;
	int count = 0;
	// using a nested for loop, compare the first element in the first array with all the values in the second array. Then apply this process to all elements in the first array.
	for (int i = 0; i < n1; i++) {
		for (int k = 0; k < n2; k++) {
			if (a1[i] == a2[k] && count == 0) {
				return i;
			}
		}
	}

	// return -1 if no values found in both arrays.
	return pos;

}
int subsequence(const string a1[], int n1, const string a2[], int n2) {
	//because the size of the subsequence array is 0, that means that it is a subsequence of any array no matter the size. This results in the function returning 0.
	if (n2 == 0) {
		return 0;
	}
	if (n2 < 0) {
		return -1;
	
	}
	// returns -1 if either the size of the first array is less than or equal to 0 , or if the subsequence array is greater in length than the primary array.
	if (n1 <= 0 || n2 > n1) {
		return -1;
	}

	
	//Using a nested for loop, iterate n1- n2 + 1 times for the outer loop, initializing a boolean value isSubsequence as true. If no subsequence found, set it to false. Continue until the subsequence is found in the first array, and it is not set to false, and then return the position of that subsequence in the array.
	// If no subsequence found, return false.
	for (int i = 0; i <= n1 - n2; i++) {
		bool isSubsequence = true;
		for (int j = 0; j < n2; j++) {
			if (a1[i + j] != a2[j]) {
				isSubsequence = false;
				break;
			}
		}
		if (isSubsequence) {
			return i;
		}
	}
	//return -1 if no value in the subsequence is found in the primary array.
	return -1; 

}
int rotateLeft(string a[], int n, int pos) {
	if (n < 0) {
		return -1;
	}



	// Starting at position of pos, iterate through the array, switching the value at position pos with the value ahead of it, continue this operation until the array has been iterated through fully.
	for (int i = pos; i < n - 1; i++) {
		string s = a[i];
		a[i] = a[i + 1];
		a[i + 1] = s;
	}
	return pos;
}
int separate(string a[], int n, string separator) {
	if (n <= 0) {
		return -1;
	}

	// A left pointer assigned to the first position and a right pointer assigned to the last position
	int left = 0;
	int right = n - 1;

	while (left <= right) {



		// while left is less than n and it's value is less than seperator, there is no need to switch the value of a[left] to the left side, because it's value is already smaller than separator. Move the left pointer right until this condition is false.
		while (left < n && a[left] < separator) {
			left++;
		}

		// while right is greater than or equal to n and it's value is greaer than or equal seperator, there is no need to switch the value of a[right] to the right side, because it's value is already greater than or equal to separator. Move the right pointer left until this condition is false.
	
		while (right >= 0 && a[right] >= separator) {
			right--;
		}

		// switch the value at the left position with the value in the right position through the use of a temporary variable, and then move the left pointer right, and the right pointer left.
		//Continue this until either both pointers point to the same value or the left pointer is to the right of the right pointer.
		if (left < right) {
			string temp = a[left];
			a[left] = a[right];
			a[right] = temp;
			left++;
			right--;
		}
	}
	// iterate through all values in n, look for first value after arrangment that is greater than or equal to seperator and return it.
	for (int i = 0; i < n; i++) {
		if (a[i] >= separator) {
			return i;
		}
	}

	return n; 
}
int flip(string a[], int n) {
	// A left pointer assigned to the first position and a right pointer assigned to the last position.
	int left = 0;
	int right = n - 1;
	// using a while loop, switch the value at the left position with the value in the right position through the use of a temporary variable, and then move the left pointer right, and the right pointer left.
	//Continue this until either both pointers point to the same value or the left pointer is to the right of the right pointer.
	while (left <= right) {
		string temp = a[left];
		a[left] = a[right];
		a[right] = temp;
		left++;
		right--;
	}
	return n;
}

