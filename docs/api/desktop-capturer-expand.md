# desktopCapturerExpand

> Monitor the bounds of the shared window

Process: [Main](../glossary.md#main-process)

## Events

The `desktopCapturerExpand` object emits the following events:

### Event: 'media-frame-bound-changed'

Returns:

* `event` Event
* `bounds` Rectangle

Emitted when the shared window bounds changes.

## Methods

The `desktopCapturerExpand` object has the following methods:

### `desktopCapturerExpand.startObserving()`

Start listening for shared window bounds.

### `desktopCapturerExpand.stopObserving()`

Stop listening for shared window bounds.