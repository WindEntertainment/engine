// import * as vscode from 'vscode';

// export function activate(context: vscode.ExtensionContext) {
//   console.log(
//     'Congratulations, your extension "temp-first-check" is now active!',
//   );

//   const disposable = vscode.commands.registerCommand(
//     'temp-first-check.helloWorld',
//     () => {
//       vscode.window.showInformationMessage(
//         'Hello World from temp_first_check!',
//       );
//     },
//   );

//   context.subscriptions.push(disposable);
// }

// export function deactivate() {}
import * as path from 'path';
import * as vscode from 'vscode';
import { exec } from 'child_process';

export function activate(context: vscode.ExtensionContext) {
  console.log('Linting extension "temp-first-check" is now active!');

  const diagnosticCollection =
    vscode.languages.createDiagnosticCollection('myLinter');

  function runLinter(document: vscode.TextDocument) {
    if (!document.fileName.endsWith('.wi')) {
      return;
    }

    // Path to the linter.js script
    const linterScript = path.join(context.extensionPath, 'linter.js');
    console.log(linterScript);

    // Execute linter.js with the file name as an argument
    // exec(
    //   `node ${linterScript} ${document.fileName}`,
    //   (error, stdout, stderr) => {
    //     if (error) {
    //       console.error(`Linter error: ${stderr}`);
    //       return;
    //     }

    //     const diagnostics: vscode.Diagnostic[] = parseLinterOutput(stdout);
    //     diagnosticCollection.set(document.uri, diagnostics);
    //   },
    // );
  }

  // function parseLinterOutput(output: string): vscode.Diagnostic[] {
  //   const diagnostics: vscode.Diagnostic[] = [];
  //   const lines = output.split('\n');

  //   for (const line of lines) {
  //     const match = line.match(/(\d+):(\d+):\s(.+)/);
  //     if (match) {
  //       const lineNumber = parseInt(match[1]) - 1;
  //       const column = parseInt(match[2]) - 1;
  //       const message = match[3];

  //       const range = new vscode.Range(
  //         lineNumber,
  //         column,
  //         lineNumber,
  //         column + 1,
  //       );
  //       const diagnostic = new vscode.Diagnostic(
  //         range,
  //         message,
  //         vscode.DiagnosticSeverity.Warning,
  //       );
  //       diagnostics.push(diagnostic);
  //     }
  //   }

  //   return diagnostics;
  // }

  // Lint on file save
  // vscode.workspace.onDidSaveTextDocument(() => {
  //   // console.log(123);
  //   // runLinter(document);
  // });

  vscode.languages.registerDocumentFormattingEditProvider(
    { pattern: '*.wi' },
    {
      provideDocumentFormattingEdits(document: vscode.TextDocument) {
        const firstLine = document.lineAt(0);
        if (firstLine.text !== '42') {
          return [vscode.TextEdit.insert(firstLine.range.start, '42\n')];
        }
      },
    },
  );

  // Register command (optional) for manual triggering
  const disposable = vscode.commands.registerCommand(
    'temp-first-check.helloWorld',
    () => {
      console.log('example');
      vscode.window.showInformationMessage(
        'Hello World!!! from temp_first_check!',
      );
    },
  );

  // context.subscriptions.push(disposable);
  // context.subscriptions.push(diagnosticCollection);
}

export function deactivate() {}
