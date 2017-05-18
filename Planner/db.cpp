#ifndef DB_CPP
#define DB_CPP

#include <iostream>
#include <fstream>
#include <stdio.h>
#include <stdlib.h>
#include <vector>

// This database like sorted array list

template<class T>
class Db {
	private:
		FILE *file;

		void writeToFile(T &data, long position) {
			long fsize = lengthOfDb();
			if (position == fsize) {
				fseek(file, position, SEEK_SET);
				fwrite(&data, sizeof(T), 1, file);
				rewind(file);
			} else {
				fseek(file, position, SEEK_SET);
				char *buffer = (char*) malloc (fsize - position);
				fread(buffer, fsize - position, 1, file);
				fseek(file, position, SEEK_SET);
				fwrite(&data, sizeof(T), 1, file);
				fwrite(buffer, fsize - position, 1, file);
				rewind(file);
				delete buffer;
			}
		}
		//find position in the database file where we will save data
		long findPosition(T &data) {
			if (file == NULL) {
				openDbFile();
			}
			long position = 0L;
			long fsize = lengthOfDb();
			if (position == fsize) {
				return position;
			}
			T temp;
			while(position < fsize) {
				fread(&temp, sizeof(T), 1, file);
				if (temp > data) {
					rewind(file);
					return position;
				}
				position += sizeof(T);
			}
			rewind(file);
			return position;
		}
		//database file size in bytes
		long lengthOfDb() {
			if (file == NULL) {
				openDbFile();
			}
			long fsize = 0L;
			fseek (file, 0, SEEK_END);
			fsize = ftell(file);
			rewind(file);
			return fsize;
		}
		//overwrite 
		bool writeToPosition(T &data, int index) {
			index -= 1;
			if (index > size() || index < 0) {
				return false;
			}
			long position = index * sizeof(T);
			fseek(file, position, SEEK_SET);
			fwrite(&data, position, 1, file);
			rewind(file);
			return true;
		}

	public:
		Db() {}

		~Db() {
			if (file != NULL) {
				fclose(file);
			}
			delete file;
		}

		void openDbFile() {
			file = fopen("db.bin", "r+b");
			if (file == NULL) {
				file = fopen("db.bin", "w+b");
			}
		}

		void closeDbFile() {
			if (file != NULL) {
				fclose(file);
			}
		}

		void add(T &data) {
			if (file == NULL) {
				openDbFile();
			}
			long position = findPosition(data);
			writeToFile(data, position);
		}

		void get(T &temp, int index) {
			if (file == NULL) {
				openDbFile();
			}
			index -= 1;
			if (index > size(temp) || index < 0) {
				exit(1);
			}
			long position = index * sizeof(T);
			fseek(file, position, SEEK_SET);
			fread(&temp, sizeof(T), 1, file);
			rewind(file);
		}

		int size(T &temp) {
			if (file == NULL) {
				openDbFile();
			}
			return lengthOfDb() / sizeof(T);
		}

		T del(T &temp, int index) {
			if (file == NULL) {
				openDbFile();
			}
			if (index > size(temp) || index < 1) {
				exit(1);
			}
			T deleted;
			if (size(temp) == 1) {
				get(deleted, 1);
				clearDb();
				return deleted;
			}
			std::vector<T> buffer;
			for (int i = 1; i <= size(temp); i++) {
				if (i == index) {
					get(deleted, i);
					continue;
				}
				get(temp, i);
				buffer.push_back(temp);
			}
			fclose(file);
			file = fopen("db.bin", "w+b");	
			for (int i = 0; i < buffer.size(); i++) {
				add(buffer[i]);
			}
			return deleted;
		}

		T deleteLast(T &temp) {
			int last = size(temp);
			return del(temp, last);
		}

		T deleteFirst(T &temp) {
			return del(temp, 1);
		}

		bool clearDb() {
			if (file != NULL) {
				fclose(file);
			}
			fopen("db.bin", "w+b");
			fclose(file);
		}
};

#endif // DB_CPP
