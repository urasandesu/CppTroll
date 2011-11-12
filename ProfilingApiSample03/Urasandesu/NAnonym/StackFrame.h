#pragma once
#ifndef URASANDESU_NANONYM_STACKFRAME_H
#define URASANDESU_NANONYM_STACKFRAME_H

namespace Urasandesu { namespace NAnonym {

    class StackFrame
    {
    public:
        StackFrame();
        void Init(HANDLE hProcess, DWORD offset);
        DWORD GetOffset();
        std::string const &GetModuleName();
        std::string const &GetSymbolName();
        DWORD GetSymbolDisplacement();
        std::string const &GetFileName();
        DWORD GetFileLineNumber();
        DWORD GetFileColumnNumber();

    private:        
        void FillSymbolInfoIfNecessary();
        bool HasGotSymbolInfo();
        void FillSymbolInfo();
        void FillFileLineInfoIfNecessary();
        bool HasGotFileLineInfo();
        void FillFileLineInfo();

        HANDLE m_hProcess;
        DWORD m_offset;

        std::string m_modName;
        std::string m_symName;
        DWORD m_symDisp;
        std::string m_fileName;
        DWORD m_fileLineNum;
        DWORD m_fileColumnNum;
    };

}}  // namespace Urasandesu { namespace NAnonym {

#endif  // URASANDESU_NANONYM_STACKFRAME_H