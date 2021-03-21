//
// Created by laugh on 2021/3/19.
//

#include <sstream>
#include "../domain/exception.h"
#include "../util/Log.h"
#include "StateTransitionTable.h"

StateTransitionTable::StateTransitionTable(RuleSet *set) {
    ruleSet = set;
    for (int i = 0; i < ruleSet->ruleNum(); ++i) {
        auto *rule = ruleSet->getRule(i);
        for (int j = 0; j < rule->ruleSeqNum(); ++j) {
            auto *ruleSeq = rule->getRuleSeq(j);
            auto *first = ruleSet->getFirstSet(ruleSeq, 0, ruleSeq->ruleItemNum());
            for (int k = 0; k < first->SymbolNum(); ++k) {
                auto *symbol = first->getSymbolByPos(k);
                if (symbol->getRuleItemType() != RuleItemType::Empty) {
                    insert(rule->getStartSymbol(), symbol, ruleSeq);
                }
            }
            if (first->hasEmptySymbol()) {
                auto *follow = ruleSet->getFollowSet(rule->getStartSymbol());
                for (int k = 0; k < follow->SymbolNum(); ++k) {
                    insert(rule->getStartSymbol(), follow->getSymbolByPos(k), ruleSeq);
                }
            }
        }
    }
}

RuleSeq *StateTransitionTable::getRuleSeq(RuleItem *startSymbol, Token *token) {
    auto pair = table.find(startSymbol->getSymbolName());
    if (pair != table.end()) {
        Log::info("find pair");
        return pair->second->get(token);
    }
    return nullptr;
}

RuleSeq *StateTransitionTable::getRuleSeq(Token *token) {
    for (int i = 0; i < ruleSet->ruleNum(); ++i) {
        auto *start = ruleSet->getRule(i)->getStartSymbol();
        auto *ruleSeq = getRuleSeq(start, token);
        if (ruleSeq != nullptr) {
            return ruleSeq;
        }
    }
    throw ParseException("can't find ruleSeq for " + token->getText());
}

bool StateTransitionTable::insert(RuleItem *startSymbol, RuleItem *terminal, RuleSeq *ruleSeq) {
    auto pair = table.find(startSymbol->getSymbolName());
    if (pair == table.end()) {
        auto *row = new TableRow;
        table[startSymbol->getSymbolName()] = row;
        if (!row->append(terminal, ruleSeq)) {
            Log::info("insert fail");
        }
    } else {
        auto *row = pair->second;
        if (!row->append(terminal, ruleSeq)) {
            throw ParseException(
                    "rule seq repeat: M[" + startSymbol->getSymbolName() + ", " + terminal->getSymbolName() + "]");
        }
    }
    std::ostringstream fmt;
    fmt << "succeed in adding M[" << startSymbol->getSymbolName();
    fmt << ", " << terminal->getSymbolName() << "] = ";
    fmt << ruleSeq->getStartSymbol()->getSymbolName() << " -> ";
    for (int i = 0; i < ruleSeq->ruleItemNum(); ++i) {
        fmt << ruleSeq->getRuleItemByPos(i)->getSymbolName() << " ";
    }
    Log::info(fmt.str());
    return true;
}

bool StateTransitionTable::TableRow::append(RuleItem *terminal, RuleSeq *ruleSeq) {
    // 先查重
    if (get(terminal) != nullptr) {
        return false;
    }
//    list.emplace_back(terminal, ruleSeq);
    map[getKey(terminal)] = std::pair(terminal, ruleSeq);
    return true;
}

RuleSeq *StateTransitionTable::TableRow::get(RuleItem *terminal) {
//    for (auto &pair : list) {
//        if (pair.first->getRuleItemType() == terminal->getRuleItemType()
//            && pair.first->getSymbolName() == terminal->getSymbolName()) {
//            return pair.second;
//        }
//    }
    auto pair = map.find(getKey(terminal));
    if (pair != map.end()) {
        return pair->second.second;
    }
    return nullptr;
}

RuleSeq *StateTransitionTable::TableRow::get(Token *token) {
//    for (auto &pair : list) {
//        if (pair.first->matchToken(token)) {
//            std::ostringstream fmt;
//            fmt << "getting from stt: " << pair.second->getStartSymbol()->getSymbolName();
//            fmt << " -> ";
//            for (int i = 0; i < pair.second->ruleItemNum(); ++i) {
//                fmt << pair.second->getRuleItemByPos(i)->getSymbolName() << " ";
//            }
//            Log::info(fmt.str());
//            return pair.second;
//        }
//    }
    auto pair = map.find(getKey(token));
    if (pair != map.end()) {
        return pair->second.second;
    }
    return nullptr;
}

std::string StateTransitionTable::TableRow::getKey(RuleItem *terminal) {
    return terminal->getSymbolName();
}

std::string StateTransitionTable::TableRow::getKey(Token *token) {
    auto tokenType = token->getTokenType();
    if (tokenType == TokenType::string) {
        return "STRING";
    } else if (tokenType == TokenType::op) {
        return "OP";
    } else if (tokenType == TokenType::number) {
        return "NUMBER";
    } else if (tokenType == TokenType::identifier) {
        return "IDENTIFIER";
    } else if (tokenType == TokenType::eof) {
        return "$";
    } else if (tokenType == TokenType::eol) {
        return "EOL";
    } else if (tokenType == TokenType::none) {
        return "NONE";
    }
    return token->getText();
}
