#ifndef BSTCHECKER_H
#define BSTCHECKER_H

#include "BSTNode.h"
#include <unordered_set>

class BSTChecker {
public:
   static BSTNode* CheckBSTValidity(BSTNode* rootNode) {
      std::unordered_set<BSTNode*> visited;
      
      struct ValidityChecker {
         std::unordered_set<BSTNode*>& visited;
         
         BSTNode* Check(BSTNode* node, int minKey, int maxKey,
            bool hasMin, bool hasMax) {
            
            if (!node) {
               return nullptr;
            }
            
            if (visited.count(node) > 0) {
               return node;
            }
            
            if (hasMax && node->key >= maxKey) {
               return node;
            }
            
            if (hasMin && node->key <= minKey) {
               return node;
            }
            
            visited.insert(node);
            
            BSTNode* result = Check(node->left, minKey, node->key, hasMin, true);
            if (result) {
               return result;
            }
            
            return Check(node->right, node->key, maxKey, true, hasMax);
         }
      };
      
      ValidityChecker checker{visited};
      return checker.Check(rootNode, 0, 0, false, false);
   }
};

#endif
