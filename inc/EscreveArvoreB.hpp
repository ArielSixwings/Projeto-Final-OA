#ifndef ESCREVE_ARVORE_B
#define ESCREVE_ARVORE_B

#include "ArvoreB.hpp"
#include <vector>
#include <sstream>

class BTreePrinter
{
   struct NodeInfo
   {
      std::string text;
      unsigned text_pos, text_end;  // half-open range
   };

   typedef std::vector<NodeInfo> LevelInfo;

   std::vector<LevelInfo> levels;

   std::string node_text (char **Chaves, unsigned key_count);

   void before_traversal ()
   {
      levels.resize(0);
      levels.reserve(10);   // far beyond anything that could usefully be printed
   }

   void visit (NodeArvoreB const *node, unsigned level = 0, unsigned child_index = 0);

   void after_traversal ();

public:
   void print (ArvoreB const &tree)
   {
      before_traversal();
      visit(tree.Raiz);
      after_traversal();
   }
   friend class ArvoreB;
   friend class NodeArvoreB;
};

#endif