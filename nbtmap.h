#ifndef _NBTMAP_
#define _NBTMAP_

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

class NBTCompound
{
    private:
        std::string data;
        std::unordered_map<std::string,std::string> nbt;
    
    public:
        NBTCompound() { data.clear(); nbt.clear(); }
        NBTCompound(std::string nbt_data) { parse(nbt_data); }
        
        std::string& operator[] (const std::string &key) { return nbt[key]; }
        friend std::ostream& operator<< (std::ostream& stream, NBTCompound &comp) { stream<<comp.get(); return stream; }
        
        size_t size() { return nbt.size(); }
        size_t erase(const std::string &key) { return nbt.erase(key); }
        void clear() { nbt.clear(); }
        
        std::unordered_map<std::string,std::string>::iterator begin() { return nbt.begin(); }
        std::unordered_map<std::string,std::string>::iterator end() { return nbt.end(); }
        std::unordered_map<std::string,std::string>::const_iterator cbegin() { return nbt.cbegin(); }
        std::unordered_map<std::string,std::string>::const_iterator cend() { return nbt.cend(); }
        
        const std::string get(const std::string &key = "")
        {
            if (key.size() < 1)
            {
                std::string full = "{";
                if (nbt.size() > 0)
                {
                    for (auto& it: nbt)
                        full = full + it.first + ": " + it.second + ", ";
                    full.erase(full.size()-2,2);
                }
                full += "}";
                return full;
            }
            auto v = nbt.find(key);
            if (v != nbt.end())
                return v->second;
            return "";
        }
        
        void set(const std::string &key, std::string value)
        {
            auto v = nbt.emplace(key,value);
            if (!v.second)
                nbt.at(key) = value;
        }
        
        void parse(std::string nbt_data = "")
        {
            if (nbt_data.size() > 0)
                data = nbt_data;
            if (nbt.size() > 0)
                nbt.clear();
            std::vector<std::string> items;
            int cBrace = 0, sBrace = 0;
            bool quote = false;
            bool starting = false;
            for (auto it = data.begin(), start = data.begin(), ite = data.end();it != ite;++it)
            {
                if (quote)
                {
                    if (*it == '\'')
                    { // Skip an escaped character
                        ++it;
                        continue;
                    }
                    if (*it != '"')
                        continue;
                    quote = false;
                }
                else if (*it == '"')
                    quote = true;
                else if (*it == '{')
                    cBrace++;
                else if (*it == '}')
                    cBrace--;
                else if (*it == '[')
                    sBrace++;
                else if (*it == ']')
                    sBrace--;
                else if ((*it != ' ') && (*it != ',') && (!starting) && (!sBrace) && (cBrace == 1))
                {
                    start = it;
                    starting = true;
                }
                if ((starting) && (!quote) && (cBrace < 2) && (!sBrace) && (*it == ','))
                {
                    items.emplace_back(start,it);
                    starting = false;
                }
                else if ((starting) && (!quote) && (!sBrace) && (*it == '}'))
                {
                    if (cBrace == 1)
                    {
                        items.emplace_back(start,it+1);
                        starting = false;
                    }
                    else if (!cBrace)
                    {
                        items.emplace_back(start,it);
                        starting = false;
                    }
                }
            }
            for (auto it = items.begin(), ite = items.end();it != ite;++it)
            {
                size_t pos = it->find(':');
                std::string key = it->substr(0,pos++), value;
                if (it->at(pos) == ' ')
                    pos++;
                value = it->substr(pos);
                nbt.emplace(key,value);
            }
        }
};

class NBTList
{
    private:
        std::string data;
        std::vector<std::string> nbt;
    
    public:
        NBTList() { data.clear(); nbt.clear(); }
        NBTList(std::string nbt_data) { parse(nbt_data); }
        
        std::string& operator[] (size_t n) { return nbt.at(n); }
        friend std::ostream& operator<< (std::ostream& stream, NBTList &list) { stream<<list.getList(); return stream; }
        
        size_t size() { return nbt.size(); }
        void push_back(std::string item) { nbt.push_back(item); }
        void clear() { nbt.clear(); }
        
        std::vector<std::string>::iterator begin() { return nbt.begin(); }
        std::vector<std::string>::iterator end() { return nbt.end(); }
        std::vector<std::string>::reverse_iterator rbegin() { return nbt.rbegin(); }
        std::vector<std::string>::reverse_iterator rend() { return nbt.rend(); }
        std::vector<std::string>::const_iterator cbegin() { return nbt.cbegin(); }
        std::vector<std::string>::const_iterator cend() { return nbt.cend(); }
        std::vector<std::string>::const_reverse_iterator crbegin() { return nbt.crbegin(); }
        std::vector<std::string>::const_reverse_iterator crend() { return nbt.crend(); }
        
        std::vector<std::string>::iterator erase(std::vector<std::string>::iterator pos) { return nbt.erase(pos); }
        std::vector<std::string>::iterator erase(std::vector<std::string>::iterator first, std::vector<std::string>::iterator last) { return nbt.erase(first,last); }
        
        size_t erase(size_t pos)
        {
            if (pos >= nbt.size())
                return 0;
            nbt.erase(nbt.begin()+pos);
            return 1;
        }
        
        size_t erase(size_t start, size_t len)
        {
            size_t initial = nbt.size();
            if (start >= nbt.size())
                return 0;
            if (start+len >= nbt.size())
                nbt.erase(nbt.begin()+start,nbt.end());
            else
                nbt.erase(nbt.begin()+start,nbt.begin()+start+len);
            return initial-nbt.size();
        }
        
        const std::string get(int pos)
        {
            if (pos < 0)
                pos = nbt.size()+pos;
            if ((pos > -1) && (pos < nbt.size()))
                return nbt[pos];
            return "";
        }
        
        const std::string get(size_t start, size_t len)
        {
            std::string full = "[";
            if ((start+1 < nbt.size()) && (len > 0))
            {
                size_t end = start+len;
                if (end > nbt.size())
                    end = nbt.size();
                for (;start < end;++start)
                    full = full + nbt[start] + ", ";
                full.erase(full.size()-2,2);
            }
            full += "]";
            return full;
        }
    
        const std::string get(std::vector<std::string>::iterator first, std::vector<std::string>::iterator last)
        {
            std::string full = "[";
            for (;first != last;++first)
                full = full + *first + ", ";
            full.erase(full.size()-2,2);
            full += "]";
            return full;
        }
        
        std::string getList()
        {
            std::string full = "[";
            if (nbt.size() > 0)
            {
                for (auto& it: nbt)
                    full = full + it + ", ";
                full.erase(full.size()-2,2);
            }
            full += "]";
            return full;
        }
        
        void parse(std::string nbt_data = "")
        {
            if (nbt_data.size() > 0)
                data = nbt_data;
            if (nbt.size() > 0)
                nbt.clear();
            int cBrace = 0, sBrace = 0;
            bool quote = false;
            bool starting = false;
            for (auto it = data.begin(), start = data.begin(), ite = data.end();it != ite;++it)
            {
                if (quote)
                {
                    if (*it == '\'')
                    { // Skip an escaped character
                        ++it;
                        continue;
                    }
                    if (*it != '"')
                        continue;
                    quote = false;
                }
                else if (*it == '"')
                    quote = true;
                else if (*it == '{')
                    cBrace++;
                else if (*it == '}')
                    cBrace--;
                else if (*it == '[')
                    sBrace++;
                else if (*it == ']')
                    sBrace--;
                if ((!quote) && (*it != '[') && (*it != ' ') && (*it != ',') && (!starting) && (sBrace == 1))
                {
                    start = it;
                    starting = true;
                }
                else if ((starting) && (!quote) && (sBrace < 2) && (!cBrace) && (*it == ','))
                {
                    nbt.emplace_back(start,it);
                    starting = false;
                }
                else if ((starting) && (!quote) && (!cBrace) && (*it == ']'))
                {
                    if (sBrace == 1)
                    {
                        nbt.emplace_back(start,it+1);
                        starting = false;
                    }
                    else if (!sBrace)
                    {
                        nbt.emplace_back(start,it);
                        starting = false;
                    }
                }
            }
        }
};

#endif

