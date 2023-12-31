#ifndef DREWNO_MARS_SYMBOL_TABLE_HPP
#define DREWNO_MARS_SYMBOL_TABLE_HPP
#include <string>
#include <unordered_map>
#include <list>

//Use an alias template so that we can use
// "HashMap" and it means "std::unordered_map"
template <typename K, typename V>
using HashMap = std::unordered_map<K, V>;

using namespace std;


namespace drewno_mars{

class ScopeTable;

//A semantic symbol, which represents a single
// variable, function, etc. Semantic symbols 
// exist for the lifetime of a scope in the 
// symbol table. 
class SemSymbol {
	//TODO add the fields that 
	// each semantic symbol should track
	// (i.e. the kind of the symbol (either a variable or function)
	// and functions to get/set those fields
	public:
		SemSymbol(std::string name, std::string kind, std::string type, ScopeTable* scope = nullptr): Name(name), Kind(kind), Type(type), AssociatedScope(scope){}
		void setName(std::string name) { Name = name; }
		void setKind(std::string kind) { Kind = kind; }
		void setType(std::string type) { Type = type; }
		void setAssociatedScope(ScopeTable* scope) { AssociatedScope = scope; }

		std::string getName() { return Name; }
		std::string getKind() { return Kind; }
		std::string getType() { return Type; }
		ScopeTable* getAssociatedScope() { return AssociatedScope; }

	private:
		std::string Name;
		std::string Kind;
		std::string Type;
		ScopeTable* AssociatedScope;
};

//A single scope. The symbol table is broken down into a 
// chain of scope tables, and each scope table holds 
// semantic symbols for a single scope. For example,
// the globals scope will be represented by a ScopeTable,
// and the contents of each function can be represented by
// a ScopeTable.
class ScopeTable {
	public:
		ScopeTable();
		//TODO: add functions for looking up symbols
		// and/or returning information to indicate
		// that the symbol does not exist within the
		// current scope.
		bool insert(std::string id, SemSymbol * symbol) {
			std::pair<std::string, SemSymbol *> item(id, symbol);
			return symbols->insert(item).second;
		}
		SemSymbol * lookup(std::string id) {
    		
			for (const auto& pair : *symbols) {
        		const std::string& symbolId = pair.first;
       			SemSymbol* symbol = pair.second;

        		// Perform specific checks on the symbol
       	 		if (symbolId == id) {
            		return symbol; // If you want to return it immediately
        		}

        		if (symbol->getAssociatedScope()) {
            		
					if(symbol->getAssociatedScope()->lookup(id) != nullptr){
						return symbol->getAssociatedScope()->lookup(id);
					}
					//return classDeclared;
        		}

        	// Continue checking other attributes of the symbol as needed
    		}

    	// If you want to return null when the symbol is not found
    		return nullptr;

		}

		/*OLD CODE
		 {
			std::unordered_map<std::string, SemSymbol *>::const_iterator item = symbols->find(id);
			if (item == symbols->end()) {
				return nullptr;
			} else {
				return item->second;
			}
		} 
		*/
		
	private:
		HashMap<std::string, SemSymbol *> * symbols;
};

class SymbolTable{
	public:
		SymbolTable();
		//TODO: add functions to create a new ScopeTable
		// when a new scope is entered, drop a ScopeTable
		// when a scope is exited, etc.
		void insert(ScopeTable * Scope) {
			scopeTableChain->push_back(Scope);
		}
		void remove() {
			scopeTableChain->pop_back();
		}
		bool insertSymbolIntoCurrentScope(SemSymbol * symbol) {
			ScopeTable * current = scopeTableChain->back();
			bool success = current->insert(symbol->getName(), symbol);
			return success;
		}
		SemSymbol * searchscopes(std::string id)
		{
			for (auto Scopes : *scopeTableChain)
			{
				SemSymbol * temp = Scopes->lookup(id);
				if (temp != nullptr)
				{
					return temp;
				}
			}
			return nullptr;
		}
		bool existsInCurrentScope(const std::string &name) const {
			return scopeTableChain->back()->lookup(name) != nullptr;
		}
	private:
		std::list<ScopeTable *> * scopeTableChain;
};

	
}

#endif
